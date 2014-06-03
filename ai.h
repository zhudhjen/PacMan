#ifndef _AI_H_
#define _AI_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "var.h"
#include "coord.h"

typedef struct tagClassAI classAI;
struct tagClassAI {
    //move the monsters
    int (*move)(classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], coord ghostPos[4], int ghostDir[4], double pacPosX, double pacPosY, int burst);
    
    double aiSpeed, playerSpeed;
    int index;
};

int moveAI(classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], coord ghostPos[4], int ghostDir[4], double pacPosX, double pacPosY, int burst);

bool checkDirection(int map[MAP_HEIGHT][MAP_WIDTH], coord pos, int direction);

int getDistance(int map[MAP_HEIGHT][MAP_WIDTH], coord pos, coord goal, int direction);

#endif /* _AI_H_ */
