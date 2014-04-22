#ifndef _FOOL_H_
#define _FOOL_H_
#include "ai.h"

typedef struct {
    //inherit from ai
    classAI ai;

} classFool;

extern void foolConstruct (classFool *this, const double ai_speed, const double player_speed);

static int foolMove (const classAI *this, const int **map, const bool burst);

extern void foolDestruct (const classAI *this);

static void foolDfs (int **map, );
#endif /*_FOOL_H_*/