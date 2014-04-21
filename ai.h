#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    //construct the AI
    void (*construct)(const classAI *this, double ai_speed, double player_speed);

    //move the monsters
    int (*move)(const classAI *this, const int **map, const bool burst);

    //be notified when game over, destruct the AI
    void (*destruct)(const classAI *this);
    
    double aiSpeed, playerSpeed;
} classAI;

