#ifndef _AI_H_
#define _AI_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "coord.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 28

typedef int bool;

const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {1, -1, 0, 0};


typedef struct {
    //move the monsters
    int (*move)(struct classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], coord ghostPos[], int ghostDir[], double pacPosX, double pacPosY, int burst);
    
    double aiSpeed, playerSpeed;
    int index;
} classAI;

int moveAI(classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], coord ghostPos[], int ghostDir[], double pacPosX, double pacPosY, int burst);

#endif /* _AI_H_ */
