#include "fool.h"
#include "ai.h"
#include "dos.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 28

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define VK_UP 0x4800
#define VK_DOWN 0x5000
#define VK_LEFT 0x4b00
#define VK_RIGHT 0x4d00
#define VK_ENTER 0x1c0d

void welcomePage();
void gameInitial();
void keyPress();
void process();
void pacmanRound();
void handleUp();
void handleDown();
void handleLeft();
void handleRight();
