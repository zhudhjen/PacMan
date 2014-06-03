#include "ai.h"
#include "fool.h"
#include <time.h>

extern void foolConstruct (classAI *this, double ai_speed, double player_speed, int ai_index)
{
    this->move = foolMove;

    this->aiSpeed = ai_speed;
    this->playerSpeed = player_speed;
    this->index = ai_index;
    srand(time(0));
}

int foolMove (classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], coord ghostPos[4], int ghostDir[4], double pacPosX, double pacPosY, int burst)
{
    bool access[4];
    int i, decision;
    for (i = 0; i < 4; ++i)
    {
        printf("%d: (%d, %d)  dir = %d\n", i, ghostPos[i].x, ghostPos[i].y, ghostDir[i]);
    }
    for (i = 0; i < 4; ++i)
    {
        if ((i + ghostDir[this->index]) % 4 != 1 &&
           checkDirection(map, ghostPos[this->index], i))
            access[i] = TRUE;
        else 
            access[i] = FALSE;
    }
    decision = rand() % 4;
    while (!access[decision])
        decision = rand() % 4;
    return decision;
}
