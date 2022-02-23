#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void timer2Init( void ) {
	OCR2 = 195;
	TIMSK |= 0b10000000;
	sei();
	TCCR2 = 0b00000101;
}


ISR( TIMER2_OVF_vect ) {
	if (OCR2 == 195) {
		PORTD = 0b10000000;
		OCR2 = 117;
		}else if(OCR2 == 117){
		PORTD = 0b00000000;
		OCR2 = 195;
	}
}


void init(){
	DDRD &= 0b11111111;
}

int main(void) {
	DDRB = 0xFF;
	init();
	
	timer2Init();
	PORTD = 0b00000000;
	
	while (1) {
		
		wait(10);
		
	}
}