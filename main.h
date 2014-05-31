#include "fool.h"
#include "ai.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 28
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

typedef struct {
	int screenX, screenY;
	int mapX, mapY;
	int moveDir;
} classPerson;
