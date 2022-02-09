#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int ledIndex = 0; //Current selected led

ISR( INT1_vect ) {	
	//next led with a check
	ledIndex++; 		
	if (ledIndex > 7){
		ledIndex = 0;
	}
	
    PORTB = (1<<ledIndex);	
}


ISR( INT2_vect ) {
	//Previous led with a check
	ledIndex--;	
	if (ledIndex < 0) {
		ledIndex = 7;
	}

    PORTB = (1<<ledIndex);		
}



int main( void ) {
	// Init I/O
	DDRD = 0x00;			//These are for the input buttons
	DDRB = 0xFF;			//These are the output leds
	PORTB = 0x01;			//Start led

	// Init Interrupt hardware
	EICRA |= 0b00111100;			
	EIMSK |= 0b00000110;			
	
	sei();				

	while (1) {		
		wait( 500 );								
	}

	return 1;
}
