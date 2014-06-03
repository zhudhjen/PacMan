#include "ai.h"
#include "expert.h"
#include <time.h>

int hghostDir[20][4], hmap[20][MAP_HEIGHT][MAP_WIDTH];
coord hghostPos[20][4];

extern void expertConstruct (classAI *this, double ai_speed, double player_speed, int ai_index)
{
    this->move = expertMove;
    this->aiSpeed = ai_speed;
    this->playerSpeed = player_speed;
    this->index = ai_index;
    srand(time(0));
}

int expertMove (classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], coord *ghostPos, int *ghostDir, double pacPosX, double pacPosY, int burst)
{
    int i, decision, tmp, ind = this->index;
    double maxe, eval;
    coord PacPos = newCoord(floor(pacPosX), floor(pacPosY));
    for (i = 0; i < 4; ++i)
        if ((i + ghostDir[this->index]) % 4 != 1 &&
                checkDirection(map, ghostPos[this->index], i))
        {
            ghostDir[this->index] = i;
            memcpy(hmap[0], map, MAP_WIDTH*MAP_HEIGHT*sizeof(int));
            memcpy(hghostPos[0], ghostPos, 4*sizeof(int));
            memcpy(hghostDir[0], ghostDir, 4*sizeof(int));
            eval = deepEval(0, 0, this, hmap[0], hghostPos[0], hghostDir[0], PacPos, burst, 0);
            if (eval > maxe)
            {
                maxe = eval;
                decision = i;
            }
        }
    return decision;
}

//The dfs function, returning the evaluation of the situation
double deepEval(int dep, int frame, classAI *this, int map[MAP_HEIGHT][MAP_WIDTH],
        coord *ghostPos, int *ghostDir, coord PacPos, int burst, double burstRate)
{
    int i, j, turn, count = 0, total = 0, frameGone = 0, dir;
    bool flag;
    double averDist, eval, maxe = 0;

    //search for a length of 10 blocks
    if (frame * this->aiSpeed >= 10 || dep>=5)
    {
        for (j = 0; j < 4; ++j)
            for (i = 0; i < 4; ++i)
                if ((i + ghostDir[j]) % 4 != 1 &&
                        checkDirection(map, ghostPos[j], i))
                {
                    total += getDistance(map, ghostPos[j], PacPos, i);
                    count++;
                }
        averDist = total / count * pow((1 - 2 * burstRate), 2);
        eval = countWeightedElement(0, map, PacPos, averDist / 2, 1);
        return eval;
    }

    //Emulate the following ghost moving
    flag = TRUE;
    while (flag)
    {
        //check whether there is any ghost who has any choice
        for (i = 0; i < 4; ++i)     //for each ghost
        {            
            count = 0;
            for (j = 0; j < 4; ++j)     //for each direction
                if ((j + ghostDir[i]) % 4 != 1 && 
                        checkDirection(map, ghostPos[i], j))
                {
                    count++;
                    dir = j;
                } 
            if (count >= 2)
            {
                flag = FALSE;
                turn = i;
            }
            else
                ghostDir[i] = dir;
        }

        //move them if each ghost has its only move direction
        if (flag)
        {
            frameGone += floor(1 / this->aiSpeed);
            for (i = 0; i < 4; ++i)
                ghostPos[i] = coordMove(ghostPos[i], ghostDir[i]);
        }
    }
    burst = max(0, burst - frameGone);
    
    //determine the rate of burst
    if (burst > 0)
        burstRate = 1;
    else
        burstRate = 1 - exp(this->playerSpeed * countWeightedElement(0, map, PacPos, 
                floor((frame + frameGone) * this->playerSpeed), 2));

    //search for the following moving
    for (i = 0; i < 4; ++i)
        if ((i + ghostDir[this->index]) % 4 != 1 &&
                checkDirection(map, ghostPos[this->index], i))
        {
            ghostDir[turn] = i;
            memcpy(hmap[dep + 1], map, MAP_WIDTH*MAP_HEIGHT*sizeof(int));
            memcpy(hghostPos[dep + 1], ghostPos, 4*sizeof(int));
            memcpy(hghostDir[dep + 1], ghostDir, 4*sizeof(int));
            eval = deepEval(dep + 1, frame + frameGone, this, hmap[dep + 1],
                    hghostPos[dep + 1], hghostDir[dep + 1], PacPos, burst, burstRate);
            if (eval > maxe)
                maxe = eval;
        }
    return maxe;
}