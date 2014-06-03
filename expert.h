#ifndef _EXPERT_H_
#define _EXPERT_H_

#include "ai.h"

extern void expertConstruct (classAI *this, double ai_speed, 
		double player_speed, int index);

static int expertMove (classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], 
		coord *ghostPos, int *ghostDir, double pacPosX, double pacPosY, int burst);

double deepEval(int dep, int frame, classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], 
		coord *ghostPos, coord PacPos, int burst, double burstRate)

#endif /*_EXPERT_H_*/
