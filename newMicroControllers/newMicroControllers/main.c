
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
		//If-statement checkt of drukknop op PINC-1 is ingedrukt
		//zoja, dan gaat het ledje knipperen
		//zoniet, dan blijft het ledje aan zonder enige instructie.
		if(PINC == 0b00000001){ 
			PORTD = 0b10000000;
			wait(500);
			PORTD = 0b00000000;
			wait(500);
		}else{
			PORTD = 0b10000000;
		}
	}
	
	
	return 1;
}

