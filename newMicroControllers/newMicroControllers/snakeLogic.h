#pragma once

typedef enum{
    MOVE = 0,
    ADD = 1
} type;

void initSnake(void);
void moveUp(type);
void moveDown(type);
void moveLeft(type);
void moveRight(type);

void gameOver(void);
