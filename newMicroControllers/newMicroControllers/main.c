#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

const char Numbers [15] = {
	0b00111111,		// 0
	0b00000110,		// 1
	0b01011011,		// 2
	0b01001111,		// 3
	0b01100110,		// 4
	0b01101101,		// 5
	0b01111101,		// 6
	0b00000111,		// 7
	0b01111111,		// 8
	0b01101111,		// 9
	0b01110111,     //A
	0b01111100,		//B
	0b00111001,		//C
	0b01011110,		//D
	0b01111001,		//E
	0b01110001		//F
};

int chosenNumber;

//Checks the number and dispalys it to the 7-segment display
void display(int digit){
	if(digit >= 0 && digit <= 15){						
		PORTD = Numbers[digit];							
	} else{
		PORTD = Numbers[14];
	}	
}

//Substracts the number with one down
void digitDOWN(){		
	display(chosenNumber--);
}

//Adds one digit to the number
void digitUP(){	
	display(chosenNumber++);
} 


int main( void ) {
	// Init I/O
	DDRD = 0xFF;			//These are for the input buttons
	PORTD = 0x00;		
	PORTB = 0x01;

	sei();				

	chosenNumber = 4;
	
	while (1) {		
		wait( 200 );	
		display(chosenNumber);	
		
		//checks if the first button is pressed
		if (PINB == 0b00000001) {
			digitUP();
		}
		
		//checks if the second button is pressed
		if (PINB == 0b00000010) {
			digitDOWN();
		}								
	}

	return 1;
}
