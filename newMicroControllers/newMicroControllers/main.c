#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "LCDHeader.h"

int main( void ) {
	_delay_ms(5000);
	
	init();
	
	_delay_ms(100);
	
	//clear_the_LCD();

	display_text("kasdjhasdjhas");
	set_cursor(5);

	while (1) {
		_delay_ms( 250 );
	}

	return 1;
}