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
    int (*move)(classAI *this, int map[MAP_HEIGHT][MAP_WIDTH],
            coord ghostPos[4], int ghostDir[4], double pacPosX, double pacPosY, int burst);
    
    double aiSpeed, playerSpeed;
    int index;
};

//call the function pointer which is initialized by the certain constructor
int moveAI(classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], 
		coord ghostPos[4], int ghostDir[4], double pacPosX, double pacPosY, int burst);

//check whether the given direction can be walked through
bool checkDirection(int map[MAP_HEIGHT][MAP_WIDTH],
		coord pos, int direction);

//get the distance from pos to goal from the given direction
int getDistance(int map[MAP_HEIGHT][MAP_WIDTH],
		coord pos, coord goal, int direction);

//count how many points of given type in given distance within the range
double countWeightedElement(int dep, int map[MAP_HEIGHT][MAP_WIDTH],
		coord pos, int range, int type);

#endif /* _AI_H_ */
