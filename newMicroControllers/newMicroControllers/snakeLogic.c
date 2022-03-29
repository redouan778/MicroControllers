#include <stdio.h>
#include "snakeLogic.h"
#include "setValues.h"



#define MAX 10

static void advanceSnake(type);
static void checkSnake();

static segment snake[MAX] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
static int length = 3;

void initSnake()
{
    for(int i = 0; i < length; i++)
    {
        segment seg = {.pos = {3 + i, 6}};
        snake[i] = seg;
    }
}

segment getSnake(int index){
	return snake[index];
}

int getSnakeLength(){
	return length;
}
void moveUp(type movementType)
{
    if (snake[0].pos[Y] == 1)
    {
        gameOver();
    } else
    {
		
        advanceSnake(movementType);
        snake[0].pos[Y]--;
        checkSnake();
    }
}

void moveDown(type movementType)
{
    if (snake[0].pos[Y] == 8)
    {
        gameOver();
    } else
    {
        advanceSnake(movementType);
        snake[0].pos[Y]++;
        checkSnake();
    }
}

void moveLeft(type movementType)
{
    if (snake[0].pos[X] == 1)
    {
        gameOver();
    } else
    {
        advanceSnake(movementType);
        snake[0].pos[X]--;
        checkSnake();
    }
}

void moveRight(type movementType)
{
    if (snake[0].pos[X] == 8)
    {
        gameOver();
    } else
    {
        advanceSnake(movementType);
        snake[0].pos[X]++;
        checkSnake();
    }
}

void clearSnake(){
	for(int i = 0; i < 10; i++){
		segment seg = {.pos = {NULL, NULL}};				
			
		snake[i] = seg;
	}
}

void gameOver()
{
	length = 3;
	gameOverICON();
	clearSnake();
	setSnakeLenghtInc(0);
	setDirection(n);
	setSnakeSpeed(25);
	initSnake();
}


static void advanceSnake(type movementType)
{
	if(length == 10) movementType = MOVE;	
	
    for(int i = 1; i < MAX; i++)
    {
		if(MAX - i <= length + 1 ){
			snake[MAX - i] = snake[MAX - i - 1];
		}
    }
	
    if (movementType == MOVE)
    {
        segment seg = {.pos = {NULL, NULL}};
        if (length < MAX) snake[length+1] = seg;
    } else
    {
        if (length < MAX) length++;
    }
}

static void checkSnake()
{
    for(int i = 1; i < length - 1; i++)
    {
        if (snake[i].pos[X] == snake[0].pos[X] && snake[i].pos[Y] == snake[0].pos[Y])
        {
            gameOver();
        }
    }
}
