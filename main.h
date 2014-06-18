#include "fool.h"
#include "normal.h"
#include "expert.h"
#include "dos.h"
#include "draw.c"

#define MAP_WIDTH 28
#define MAP_HEIGHT 32

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define VK_UP 0x4800
#define VK_DOWN 0x5000
#define VK_LEFT 0x4b00
#define VK_RIGHT 0x4d00
#define VK_ENTER 0x1c0d
#define VK_ESC 0x011b
#define VK_SPACE 0x3920

int welcomePage();
void gameInitial();
void keyPress();
void process();
void eventHandler();
double mapToscreen(int n);

void pacmanRound();
void handleUp();
void handleDown();
void handleLeft();
void handleRight();
void changeDir();

void ghostRound();
void handleGhostUp(int i);
void handleGhostDown(int i);
void handleGhostLeft(int i);
void handleGhostRight(int i);
void changeGhostDir(int i);
