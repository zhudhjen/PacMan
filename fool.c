#include "ai.h"
#include "fool.h"

extern void foolConstruct (classFool *this, double ai_speed, double player_speed, int ai_index)
{
    this->base.move = foolMove;

    this->base.aiSpeed = ai_speed;
    this->base.playerSpeed = player_speed;
    this->base.index = ai_index;
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
