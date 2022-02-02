
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
	int speed = 500; //knipper snelheid als variable opgeslagen.
	
	while (1) {
		PORTD = 0b10000000; //Led gaat aan voor een half seconde.
		wait(speed);  
		PORTD = 0b00000000; // led gaat uit voor een half seconde.
		wait(speed);
	
		// check of de juiste knop wordt ingedrukt om te bepalen wat de snelheid is.
		if (PINC == 0b00000001) {
			//Deze if-statement checkt op welke snelheid het lampje knippert en pas het zodanig aan.
			if(speed == 500) {
				speed = 125;
			} else {
				speed = 500;
			}
		}
	}
	
	return 1;
}

