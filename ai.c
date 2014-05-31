#include "ai.h"

int moveAI (const classAI *this, const int **map, const int *ghostPos, const double pacPos, const int burst)
{
    return this->move(this, map, ghostPos, pacPos, burst);
}
