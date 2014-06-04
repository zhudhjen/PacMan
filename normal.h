#ifndef _NORMAL_H_
#define _NORMAL_H_

#include "ai.h"

extern void normalConstruct (classAI *this, double ai_speed, double player_speed, int index);

static int normalMove (classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], coord ghostPos[4], int ghostDir[4], double pacPosX, double pacPosY, int burst);

#endif /*_NORMAL_H_*/
