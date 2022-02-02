
#define F_CPU 8e6
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

void wait( int ms ){
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );
	}	
}

int ledIds[3] = {0b00000001, 0b00000010, 0b00000100};
	

void setCharliePlexingLed(int led){
	switch(led){
		case 1:
		DDRD = 0b11111011;
		PORTD = ledIds[0];
		
		break;
		case 2:
		DDRD = 0b11111011;
		PORTD = ledIds[1];
		break;
		
		case 3:
		DDRD = 0b11111110;
		PORTD = ledIds[1];
		break;
		
		case 4:
		DDRD = 0b11111110;
		PORTD = ledIds[2];
		break;
		case 5:
		DDRD = 0b11111101;
		PORTD = ledIds[0];
		break;
		case 6:
		DDRD = 0b11111101;
		PORTD = ledIds[2];
		break;
	}
	
}	
	
int main( void ) {
	DDRD = 0b11111111; // Alle pins van DDRD worden als output gezet.
	
		int i = 1;
		
		while(1){
			
			setCharliePlexingLed(i);
			i++;
			
			if (i > 6)
			{
				i= 1;
			}
			
			wait(500);				
		
	}
	
	return 1;
}

