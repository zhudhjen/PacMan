#include "fool.h"

extern void foolConstruct (classFool *this, const double ai_speed, const double player_speed)
{
    this->ai.move = foolMove;

    this->ai.aiSpeed = ai_speed;
    this->ai.playerSpeed = player_speed;

    printf("AI 'fool' constructed. \n");
}

static int foolMove (const classAI *this, const int **map, const int *ghostPos, const double pacPos, const int burst)
{
    printf("alive\n");
}

extern void foolDestruct (const classAI *this)
{
    printf("AI 'fool' destructed. \n");
}