#include "ai.h"
#include "fool.h"

extern void foolConstruct (classAI *this, double ai_speed, double player_speed, int ai_index)
{
    this->move = foolMove;

    this->aiSpeed = ai_speed;
    this->playerSpeed = player_speed;
    this->index = ai_index;
    printf("AI 'fool' constructed. \n");
}

static int foolMove (classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], coord ghostPos[], int ghostDir[], double pacPosX, double pacPosY, int burst)
{
    printf("Move Alive\n");
    return 0;
}

extern void foolDestruct (classAI *this)
{
    printf("AI 'fool' destructed. \n");
}
