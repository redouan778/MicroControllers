#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include "snakeLogic.h"
#include <avr/interrupt.h>

typedef enum{n, o, z, w} snake_direction;

static snake_direction current_direction = n;

void twi_init(void){
	TWSR = 0;
	TWBR = 32;	 // TWI clock set to 100kHz, prescaler = 0
}

void twi_start(void){
	TWCR = (0x80 | 0x20 | 0x04);
	while( 0x00 == (TWCR & 0x80) );
}

void twi_stop(void){
	TWCR = (0x80 | 0x10 | 0x04);
}

void twi_tx(unsigned char data){
	TWDR = data;
	TWCR = (0x80 | 0x04);
	while( 0 == (TWCR & 0x80) );
}

void wait( int ms ){
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void sendCommand(int addres, int byte){
		twi_start();
		twi_tx(0xE0);		// Display I2C addres + R/W bit
		twi_tx(addres);	    // rij
		twi_tx(byte);		// kolumn
		twi_stop();
}

void clearMatrixBoard(){	
	sendCommand(0x00, 0x00);
	sendCommand(0x02, 0x00);
	sendCommand(0x04, 0x00);
	sendCommand(0x06, 0x00);
	sendCommand(0x08, 0x00);
	sendCommand(0x0A, 0x00);
	sendCommand(0x0C, 0x00);
	sendCommand(0x0E, 0x00);	
}

void startTWI(){
	
	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit
	twi_tx(0x21);	// Internal osc on (page 10 HT16K33)
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xA0);	// HT16K33 pins all output
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xE3);	// Display Dimming 4/16 duty cycle
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0x81);	// Display OFF - Blink On
	twi_stop();
}

void display_snake(){
	int toSend[8] = {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00};
	
	for (int i = 0; i < 10; i++) {
		segment currentSegment = getSnake(i);
		
		int x = currentSegment.pos[X];
		int y = currentSegment.pos[Y];


		if (x == 1) {
			x = 0x80;
			} else{
			x = 1<<(x - 1);
		}
		
		toSend[y - 1] |= x;
	}
	
	for (int i = 0; i < 8; i++)
	{
		sendCommand(2 * i, toSend[i]);
	}
	
}

ISR(INT4_vect){
	current_direction = w;
	sendCommand(8, 0x80);
}

ISR(INT5_vect){
	current_direction = z;
	sendCommand(6, 0x80);
}

ISR(INT6_vect){
	current_direction = o;
		sendCommand(4, 0x80);
}

ISR(INT7_vect){
	current_direction = n;
	sendCommand(2, 0x80);
}

int main( void ){
	EICRB = 0b11111111; 
	EIMSK = 0b11110000; 
	
	sei();
	DDRE = 0b00000000;
	
	twi_init();		// Init TWI interface
	startTWI();
	
	initSnake();
	clearMatrixBoard();		
	
	wait(500);

	while(1){
		display_snake();
		wait(10);
	}			

	return 1;
}

