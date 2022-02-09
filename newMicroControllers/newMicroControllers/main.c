
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
	
//methode zorgt ervoor dat er bepaalt wordt door de switch-case wat de volgerde wordt en wat de tri-state wordt.
void setCharliePlexingLed(int led){
	switch(led){
		case 1:
		DDRD = 0b11111011;
		PORTD = ledIds[0];
		asdasdas
		break;sdfsdfs
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
		//De methode met als parameter welke lampje aan de beurt is.
		setCharliePlexingLed(i);
		
		//Na het versturen wordt het met één opgehoogd om de volgende lamp aan te roepen.
		i++;
			
		//Check of de 6e lamp al is aangeroepen zoja, dan begint de teller weer op 1;
		if (i > 6) {
			i = 1;
		}			
		wait(500);						
	}
	
	return 1;
}

