#pragma once

typedef enum{
    MOVE = 0,
    ADD = 1
} type;

typedef struct{
	int pos[2];
} segment;


#define X 0
#define Y 1

void initSnake(void);
void moveUp(type);
void moveDown(type);
void moveLeft(type);
void moveRight(type);
int getSnakeLength();

void gameOver(void);
segment getSnake(int index);
