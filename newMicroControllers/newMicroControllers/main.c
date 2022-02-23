
#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}


void init(){
	DDRD &= 0b01111111;
	TCCR2 = 0b00000111;
}

int main(void) {
	DDRB = 0xFF;
	init();
	
	while (1) {
		PORTB = TCNT2;
		wait(10);
	}
}