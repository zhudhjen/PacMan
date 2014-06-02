#include "ai.h"
#include "expert.h"
#include <time.h>

int burstRate, tburst, time;
int tmap[MAP_HEIGHT][MAP_WIDTH];
coord tghostPos[4];
int tghostDir[4];

extern void expertConstruct (classAI *this, double ai_speed, double player_speed, int ai_index)
{
    this->move = expertMove;

    this->aiSpeed = ai_speed;
    this->playerSpeed = player_speed;
    this->index = ai_index;
    printf("AI 'expert' constructed. \n");
    srand(time(0));
}

int expertMove (classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], coord *ghostPos, int *ghostDir, double pacPosX, double pacPosY, int burst)
{
    double maxe, eval[4];
    int decision, tmp, ind = this->index;
    coord PacPos = newCoord(floor(pacPosX), floor(pacPosY));
    for (i = 0; i < 4; ++i)
        if ((i + ghostDir[this->index]) % 4 != 1 &&
                checkDirection(map, ghostPos[this->index], i))
        {
            memcpy(tmap, bbs map, sizeof(map));
            memcpy(tghostPos, ghostPos, sizeof(ghostPos));
            memcpy(tghostDir, ghostDir, sizeof(ghostDir));
            time = 0;
            tburst = burst;
            burstRate = 0;
            tmp = ghostDir[ind];
            ghostDir[ind] = i;
            eval[i] = deepEval(time, this, ind, tmap, tghostPos, tghostDir, PacPos, &tburst);
            if (eval[i] > maxe)
                decision = i;
            ghostDir[ind] = tmp;
        }
    return decision;
}

double deepEval(int time, classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], coord *ghostPos, coord PacPos, int *burst)
{
    coord tmp, posBackup[4];
    bool flag, dir[4];
    int count = 0, i, total = 0, timeGone = 0;
    double val;
    //search for a length of 10 blocks
    if (time >= 10 / this->aiSpeed)
    {
        for (j = 0; j < 4; ++j)
            for (i = 0; i < 4; ++i)
                if ((i + ghostDir[j]) % 4 != 1 &&
                        checkDirection(map, ghostPos[j], i))
                {
                    total += getDistance(map, ghostPos[j], 
                        newCoord(floor(pacPosX), floor(pacPosY)), i);
                    count++;
                }
        val = total / count * pow((1 - 2 * burstRate), 2) ;
        return val;
    }

    //Emulate the following ghost moving
    flag = TRUE;
    while (flag)
    {
        //check whether there is any ghost who has any choice
        for (i = 0; i < 4; ++i)
        {            
            count = 0;
            for (j = 0; j < 4; ++j)
            {
                dir[j] = FALSE;                
                if (checkDirection(ghostPos[i], j))
                {
                    count++;
                    if ((dir[j] + ghostzDir[i]) % 4 != 1)
                    {
                        ghostDir[i] = j;
                        dir[j] = TRUE;
                    }
                }
            }
            if (count >= 3)
            {
                flag = FALSE;
                turn = i;
            }
        }

        //move them if each ghost has its only move direction
        if (flag)
        {
            timeGone += this->aiSpeed;
            for (i = 0; i < 4; ++i)
                ghostPos[i] = coordMove(ghostPos[i], i);
        }
    }

    //search for the following moving
    for (int i = 0; i < 4; ++i)
        if ((i + ghostDir[this->index]) % 4 != 1 &&
                checkDirection(map, ghostPos[this->index], i))
        {
            burstRate = 0;
            tmp = ghostDir[ind];
            ghostDir[ind] = i;
            eval[i] = deepEval(0, ind, map, ghostPos, ghostDir, PacPos, burst);
            if (eval[i] > maxe)
                decision = i;
            ghostDir[ind] = tmp;
        }
}