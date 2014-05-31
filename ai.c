#include "ai.h"

int moveAI (classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], coord ghostPos[], int ghostDir[], double pacPosX, double pacPosY, int burst)
{
    return this->move(this, map, ghostPos, ghostDir, pacPosX, pacPosY, burst);
}
