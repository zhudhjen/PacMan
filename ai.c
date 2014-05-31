#include "ai.h"

int moveAI (classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], coord *ghostPos, int *ghostDir, double pacPosX, double pacPosY, int burst)
{
    return this->move(this, map, ghostPos, ghostDir, pacPosX, pacPosY, burst);
}

bool checkDirection(int map[MAP_HEIGHT][MAP_WIDTH], coord pos, int direction)
{
    int tx = (pos.x + MAP_WIDTH + dx[direction]) % MAP_WIDTH;
    int ty = (pos.y + MAP_HEIGHT + dy[direction]) % MAP_HEIGHT;
    if (map[ty][tx] == 0)
        return FALSE;
    else
        return TRUE;
}
