#include "ai.h"

int moveAI (const classAI *this, const int **map, const bool burst)
{
    return this->move(this, map, burst);
}
