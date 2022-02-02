
#define F_CPU 8e6
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

void wait( int ms ){
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );
	}	
}

int main( void ) {
	DDRD = 0b11111111; // Alle pins van DDRD worden als output gezet.
	
	while (1) {
		PORTD = 0b10000000; //het eerste ledje van port-D wordt aangeroepen.
		wait(500);
		PORTD = 0b01000000; //het tweede ledje van port-D wordt aangeroepen.
		wait(500);
	}
	return 1;
}

