#ifndef _AI_H_
#define _AI_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int bool;

typedef struct tagClassAI classAI;
typedef struct tagClassAI {
    //move the monsters
    int (*move)(const classAI *this, const int **map, const int *ghostPos, const double pacPos, const int burst);
    
    double aiSpeed, playerSpeed;
} classAI;

int moveAI (const classAI *this, const int **map, const int *ghostPos, const double pacPos, const int burst);

#endif /*_AI_H_*/
