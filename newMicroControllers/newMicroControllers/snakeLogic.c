#include <stdio.h>
#include "snakeLogic.h"



#define MAX 10

static void advanceSnake(type);
static void checkSnake();

static segment snake[MAX] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
static int length = 3;

void initSnake()
{
    for(int i = 0; i < length; i++)
    {
        segment seg = {.pos = {3 + i, 3}};
        snake[i] = seg;
    }
}

segment getSnake(int index){
	return snake[index];
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

void gameOver()
{
    //ToDo game over.
}

static void advanceSnake(type movementType)
{
    for(int i = 1; i < MAX - 1; i++)
    {
        snake[MAX - i] = snake[MAX - i - 1];
    }
    if (movementType == MOVE)
    {
        segment seg = {.pos = {NULL, NULL}};
        if (length < MAX) snake[length] = seg;
    } else
    {
        if (length < MAX) length++;
    }
}

static void checkSnake()
{
    for(int i = 1; i < MAX - 1; i++)
    {
        if (snake[i].pos[X] == snake[0].pos[X] && snake[i].pos[Y] == snake[0].pos[Y])
        {
            gameOver();
        }
    }
}
