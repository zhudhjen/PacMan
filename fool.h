#ifndef _FOOL_H_
#define _FOOL_H_

#include "ai.h"

extern void foolConstruct (classAI *this, double ai_speed, double player_speed, int index);

static int foolMove (classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], coord ghostPos[], int ghostDir[], double pacPosX, double pacPosY, int burst);

extern void foolDestruct (classAI *this);

static void foolDfs (int map[MAP_HEIGHT][MAP_WIDTH], coord position);
#endif /*_FOOL_H_*/
