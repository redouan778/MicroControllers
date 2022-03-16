#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include "snakeLogic.h"

void twi_init(void){
	TWSR = 0;
	TWBR = 32;	 // TWI clock set to 100kHz, prescaler = 0
}

void twi_start(void){
	TWCR = (0x80 | 0x20 | 0x04);
	while( 0x00 == (TWCR & 0x80) );
}

void twi_stop(void){
	TWCR = (0x80 | 0x10 | 0x04);
}

void twi_tx(unsigned char data){
	TWDR = data;
	TWCR = (0x80 | 0x04);
	while( 0 == (TWCR & 0x80) );
}

void wait( int ms ){
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void sendCommand(int addres, int byte){
		twi_start();
		twi_tx(0xE0);		// Display I2C addres + R/W bit
		twi_tx(addres);	    // rij
		twi_tx(byte);		// kolumn
		twi_stop();
}

void clearMatrixBoard(){
	
	sendCommand(0x02, 0x00);
	sendCommand(0x04, 0x00);
	sendCommand(0x06, 0x00);
	sendCommand(0x08, 0x00);
	sendCommand(0xA0, 0x00);
	sendCommand(0xC0, 0x00);
	
		/*
	for (int i = 1; i < 8; i++)
	{
		twi_start();
		twi_tx(0x00);	// Display I2C addres + R/W bit
		twi_tx(1 << i);	// Internal osc on (page 10 HT16K33)
		twi_stop();
	}
	*/		
}

void startTWI(){
	
	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit
	twi_tx(0x21);	// Internal osc on (page 10 HT16K33)
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xA0);	// HT16K33 pins all output
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xE3);	// Display Dimming 4/16 duty cycle
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0x81);	// Display OFF - Blink On
	twi_stop();
}


int main( void ){
	
	twi_init();		// Init TWI interface
	startTWI();
	
	initSnake();
	clearMatrixBoard();	
	
	//Dit zorgt ervoor dat je de array INIT
	/*	segment *snake = getSnake();
	
	for (int i = 0; i < 10; i++)
	{
		segment currentSegment = *(snake + sizeof(*snake));
				
		int x = currentSegment.pos[X];
		int y = currentSegment.pos[Y];
		
		if (x == 1) {
			x = 0x80;
		} else{
			x = 1<<x;
		}
		
		sendCommand(1<<y, x);
		
		//DIT HIER onder kan weg ALS HET GOED IS!!!
		twi_start();
		twi_tx(0xE0);	// Display I2C addres + R/W bit
		twi_tx(1<<y);	// Address
		twi_tx(x);	// data
		twi_stop();
	}	
	*/


	while (1)
	{
		twi_start();
		twi_tx(0xE0);	// Display I2C addres + R/W bit
		twi_tx(0x04);	// Address
		twi_tx(0x00);	// data
		twi_stop();

		wait(500);	

		twi_start();
		twi_tx(0xE0);	// Display I2C addres + R/W bit
		twi_tx(0x04);	// Address RIJ
		twi_tx(0x08);	// data  KOLUMN
		twi_stop();	

		wait(500);
	}	

	return 1;
}
