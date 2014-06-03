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
    printf("AI 'expert' constructed. \n");
    srand(time(0));
}

int expertMove (classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], coord *ghostPos, int *ghostDir, double pacPosX, double pacPosY, int burst)
{
    int decision, tmp, ind = this->index;
    double maxe, eval;
    coord PacPos = newCoord(floor(pacPosX), floor(pacPosY));
    for (i = 0; i < 4; ++i)
        if ((i + ghostDir[this->index]) % 4 != 1 &&
                checkDirection(map, ghostPos[this->index], i))
        {
            frame = 0;
            ghostDir[this->index] = i;
            memcpy(hmap[0], map, sizeof(map));
            memcpy(hghostPos[0], ghostPos, sizeof(ghostPos));
            memcpy(hghostDir[0], ghostDir, sizeof(ghostDir));
            eval = deepEval(0, frame, this, ind, hmap[0], hghostPos[0], hghostDir[0], PacPos, burst, 0);
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
        coord *ghostPos, coord PacPos, int burst, double burstRate)
{
    int turn, count = 0, i, total = 0, frameGone = 0;
    bool flag, dir[4];
    double val, eval[4];

    //search for a length of 10 blocks
    if (frame * this->aiSpeed >= 10 || dep>=20)
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
        for (i = 0; i < 4; ++i)     //for each ghost
        {            
            count = 0;
            for (j = 0; j < 4; ++j)     //for each direction
            {
                dir[j] = FALSE;                
                if (checkDirection(ghostPos[i], j))
                {
                    count++;
                    if ((dir[j] + ghostDir[i]) % 4 != 1)
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
            frameGone += floor(1 / this->aiSpeed);
            for (i = 0; i < 4; ++i)
                ghostPos[i] = coordMove(ghostPos[i], i);
        }
    }
    burst = max(0, burst - frameGone);
    //search for the following moving
    for (int i = 0; i < 4; ++i)
        if ((i + ghostDir[this->index]) % 4 != 1 &&
                checkDirection(map, ghostPos[this->index], i))
        {
            ghostDir[turn] = i;
            memcpy(hmap[dep + 1], map, sizeof(map));
            memcpy(hghostPos[dep + 1], ghostPos, sizeof(ghostPos));
            memcpy(hghostDir[dep + 1], ghostDir, sizeof(ghostDir));
            eval = deepEval(dep + 1, frame + frameGone, this, ind, hmap[dep + 1],
                    hghostPos[dep + 1], hghostDir[dep + 1], PacPos, burst, br);
            if (eval[i] > maxe)
            {

            }
        }
}