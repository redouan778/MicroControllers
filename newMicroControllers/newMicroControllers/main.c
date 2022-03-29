#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include "snakeLogic.h"
#include "setValues.h"
#include <avr/interrupt.h>

static snake_direction current_direction = n;

void setDirection(snake_direction dir){
	current_direction = dir;
}

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
	sendCommand(0x00, 0x00);
	sendCommand(0x02, 0x00);
	sendCommand(0x04, 0x00);
	sendCommand(0x06, 0x00);
	sendCommand(0x08, 0x00);
	sendCommand(0x0A, 0x00);
	sendCommand(0x0C, 0x00);
	sendCommand(0x0E, 0x00);	
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

void display_snake(){
	int toSend[8] = {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00};	
	
	for (int i = 0; i < getSnakeLength(); i++) {
		segment currentSegment = getSnake(i);
		
		int x = currentSegment.pos[X];
		int y = currentSegment.pos[Y];

		if (x == 1) {
			x = 0x80;
			} else{
			x = 1<<(x - 2);
		}
		
		toSend[y - 1] |= x;
	}	
	
	for (int i = 0; i < 8; i++)
	{
		sendCommand(2 * i, toSend[i]);
	}
	
}

static int timerCounter = 0;
static int snakeLengthInc = 0;
static int snakeSpeed = 25;

void setSnakeSpeed(int speed){
	snakeSpeed = speed;
}


void setSnakeLenghtInc(int snakelengt){
	snakeLengthInc = snakelengt;
}

ISR(TIMER2_COMP_vect){
	timerCounter++;
	if (timerCounter > snakeSpeed) {
	
		type movement = MOVE;
		if (snakeLengthInc > 4)
		{
			if (snakeSpeed > 13)
			{
				snakeSpeed -= 2;
			}
			
			movement = ADD;
			snakeLengthInc = 0;
		}

		switch(current_direction){
			case(n):
				moveUp(movement);		
			break;
				
			case(o):
			moveRight(movement);		
			break;
		
			case(z):
			moveDown(movement);		
			break;
		
			case(w):
			moveLeft(movement);		
			break;
		}		
			
	
		snakeLengthInc++;
		timerCounter = 0;
	}	
		
}

void gameOverICON(){
	int cross[8] = {0XC0, 0X21, 0X12, 0X0C, 0X0C, 0X12, 0X21, 0XC0};		
	for (int i = 0; i < 8; i++)
	{
		sendCommand(2 * i, cross[i]);
	}
	
	
}

ISR(INT4_vect){
	current_direction = w;
	//sendCommand(8, 0x80);
}

ISR(INT5_vect){
	current_direction = z;
	//sendCommand(6, 0x80);
}

ISR(INT6_vect){
	current_direction = o;
	//sendCommand(4, 0x80);
}

ISR(INT7_vect){
	current_direction = n;
	//sendCommand(2, 0x80);
}

int main( void ){
	EICRB = 0b11111111; 
	OCR2 = 255;
	EIMSK = 0b11110000; 
	TIMSK = 0b10000000;
	
	sei();

	TCCR2 = 0b00011101;

	DDRE = 0b00000000;
	
	twi_init();		// Init TWI interface
	startTWI();
	
	initSnake();
	clearMatrixBoard();		
	
	wait(500);

	while(1){
		display_snake();
		wait(500);
	}			

	return 1;
}

