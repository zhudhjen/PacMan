#include "ai.h"
#include "normal.h"
#include <time.h>

extern void normalConstruct (classAI *this, double ai_speed, double player_speed, int ai_index)
{
    this->move = normalMove;

    this->aiSpeed = ai_speed;
    this->playerSpeed = player_speed;
    this->index = ai_index;
    printf("AI 'normal' constructed. \n");
    srand(time(0));
}

int normalMove (classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], coord *ghostPos, int *ghostDir, double pacPosX, double pacPosY, int burst)
{
    bool access[4];
    int decision, i, mind=999, maxd=0, distance[4];
    for (i = 0; i < 4; ++i)
    {
        if ((i + ghostDir[this->index]) % 4 != 1 &&
           checkDirection(map, ghostPos[this->index], i))
        {
            access[i] = TRUE;
            distance[i] = getDistance(map, ghostPos[this->index], 
                newCoord(floor(pacPosX), floor(pacPosY)), i);
            if (distance[i] < mind)
            {
                mind = distance[i];
                decision = i;
            }
            if (distance[i] > maxd)
            {
                maxd = distance[i];
            }
        }
        else 
            access[i] = FALSE;
    }
    if (mind > 30 || (maxd - mind < 3 && mind > 5))
    {
        decision = rand() % 4;
        while (!access[decision])
            decision = rand() % 4;
    }
    return decision;
}
