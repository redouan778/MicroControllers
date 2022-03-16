#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#define BIT(x)	(1 << (x))




#define LCD_E 	6  // RA6 UNI-6
#define LCD_RS	4  // RA4 UNI-6

void lcd_strobe_lcd_e(void);
void init_4bits_mode(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_cmd(unsigned char byte);
void lcd_clear(void);


// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms ){
	for (int tms=0; tms<ms; tms++){
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}

void lcd_strobe_lcd_e(void) {
	PORTA |= (1<<LCD_E);	// E high
	_delay_ms(1);			// nodig
	PORTA &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);			// nodig?
}


void init() {
	// PORTC output mode and all low (also E and RS pin)
	
	DDRC = 0xFF;
	PORTC = 0xFF;
	
	DDRD = 0xFF;
	DDRA = 0xFF;
	PORTC = 0x00;
	PORTA = 0x00;
	

	// Step 2 (table 12)
	PORTC = 0x20;	// function set
	lcd_strobe_lcd_e();

	// Step 3 (table 12)
	PORTC = 0x20;   // function set
	lcd_strobe_lcd_e();
	PORTC = 0x80;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Display on/off control
	lcd_strobe_lcd_e();
	PORTC = 0xF0;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Entry mode set
	lcd_strobe_lcd_e();
	PORTC = 0x60;
	lcd_strobe_lcd_e();
}


void display_text(char *str) {
	
	for(;*str; str++){
		
		unsigned char byte = *str;
		
		PORTC = byte;
		PORTA |= (1<<LCD_RS);
		lcd_strobe_lcd_e();

		// Second nibble
		PORTC = (byte<<4);
		PORTA |= (1<<LCD_RS);
		lcd_strobe_lcd_e();
	}
}


void lcd_write_command(unsigned char byte) {
	// First nibble.
	PORTC = byte;
	PORTA &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTA &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();
}


void clear_the_LCD() {
	lcd_write_command (0x01);
	_delay_ms(200);
	lcd_write_command (0x80);
}

void set_cursor(int position) {
	lcd_write_command((position | (1<<7)));
}










// Initialize ADC: 
void adcInit( void ){
	ADMUX = 0b11100001;			// AREF=2,56 V, result left adjusted, channel1 at pin PF1
	ADCSRA = 0b10000110;		// ADC-enable, no interrupt, no free running, division by 64
}


// Main program: Counting on T1
int main( void ){
	init();

	DDRF = 0x00;					// set PORTF for input (ADC)
	DDRA = 0xFF;					// set PORTA for output 
	adcInit();						// initialize ADC

	int currentValue;
	char* valueConverter;
	while (1) {			
		ADCSRA |= BIT(6);				// Start ADC
		while ( ADCSRA & BIT(6) ) ;		// Wait for completion
		PORTA = ADCH;	
		
		currentValue = ADCH + ADCL * 256;						
			
		sprintf(valueConverter, "%d", currentValue);		
		
		display_text(valueConverter);
		wait(500);						// every 50 ms (busy waiting)
	}
}