/*
 * setValues.h
 *
 * Created: 29-3-2022 15:17:43
 *  Author: HP
 */ 


#ifndef SETVALUES_H_
#define SETVALUES_H_

typedef enum{n, o, z, w} snake_direction;

void setDirection(snake_direction);

void setSnakeSpeed(int speed);

void setSnakeLenghtInc(int snakelengt);



#endif /* SETVALUES_H_ */