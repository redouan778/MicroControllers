
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
		int i = 0;
		
		while (1){
			PORTD = (1 << i);
			i++;
			
			if (i > 7){
				i = 0;
			}
			wait(50);
		}
	}	
	
	return 1;
}

