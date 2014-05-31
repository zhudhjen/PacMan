#ifndef _AI_H_
#define _AI_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "var.h"
#include "coord.h"

typedef struct {
    //move the monsters
    int (*move)(struct classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], coord *ghostPos, int *ghostDir, double pacPosX, double pacPosY, int burst);
    
    double aiSpeed, playerSpeed;
    int index;
} classAI;

int moveAI(classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], coord *ghostPos, int *ghostDir, double pacPosX, double pacPosY, int burst);

bool checkDirection(int map[MAP_HEIGHT][MAP_WIDTH], coord pos, int direction);

#endif /* _AI_H_ */
