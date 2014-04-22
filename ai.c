#include "ai.h"

void aiConstruct (const classAI *this, double ai_speed, double player_speed)
{
    this->construct(this, ai_speed, player_speed);
}

int aiMove (const classAI *this, const int **map, const bool burst)
{
    return this->move(this, map, burst);
}

void aiDesruct (const classAI *this)
{
    this->destruct(this);
}