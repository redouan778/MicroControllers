#include <stdio.h>
#include "snakeLogic.h"

#define X 0
#define Y 1

#define MAX 10

static void advanceSnake(type);

typedef struct{
    int pos[2];
} segment;

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

void moveUp(type movementType)
{
    if (snake[0].pos[Y] == 1)
    {
        gameOver();
    } else
    {
        advanceSnake(movementType);
        snake[0].pos[Y]--;
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
