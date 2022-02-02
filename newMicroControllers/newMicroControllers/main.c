
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
	
	//array dat alle pins bevat inclucsief adres.
	int ledIds[8] = {0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000, 0b10000000};
	
	//counter dat bij houdt welke index het is van de array hierboven
	int i = 0;
	
	while (1){
		PORTD = ledIds[i];
	
		i++;
	
		//checkt of de counter niet boven 7 komt om een indexoutofbounds te voorkomen. Dan wordt de counter weer op 0 gezet.
		if (i > 7){
			i = 0;
		}	
		wait(50);
	}
	
	return 1;
}

