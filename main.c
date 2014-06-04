#include "ai.c"
#include "fool.c"
#include "normal.c"
#include "coord.h"
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


struct Global {
  int score;
  int life;
  int gameover;
  int dou;
} global;

struct Pacman {
  double screenX, screenY;
  int mapX, mapY;
  int dir;
  int operation;
  double speed;
} pacman;

struct Ghost {
  double screenX, screenY;
  int mapX, mapY;
  int dir;
  classAI ai;
  int burst;
  double speed;
} ghost[4];

int map[32][28] = {
// 0  1  2  3  4  5     7     9     11    13    15    17    19    21    23    25    27 
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
  {0, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 3, 0},
  {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 4, 4, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 4, 4, 4, 4, 4, 4, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 4, 4, 4, 4, 4, 4, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 4, 4, 4, 4, 4, 4, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
  {0, 3, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 3, 0},
  {0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int mapOrigin[32][28] = {
// 0  1  2  3  4  5     7     9     11    13    15    17    19    21    23    25    27 
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
  {0, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 3, 0},
  {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 4, 4, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 4, 4, 4, 4, 4, 4, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 4, 4, 4, 4, 4, 4, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 4, 4, 4, 4, 4, 4, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
  {0, 3, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 3, 0},
  {0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

double mapToscreen(int n) {
  return n * UNIT + OFFSET;
}

int welcomePage() {
  int mode = 0;
  int key;
  drawWelcomePage(mode);
  while (1) {
    if (bioskey(2))
      key = bioskey(0);
    else 
      key = 0;
    switch (key) {
      case VK_UP:
          mode--;
          if (mode < 0)
            mode = 2;
          break;
      case VK_DOWN:
          mode = (mode + 1) % 3;
          break;
      case VK_ENTER:
          return mode;
      case VK_ESC:
          global.gameover = 1;
          return mode;
    }
    drawWelcomePage(mode);
  }
}

void gameInitial() {
  int i;
  initMap(map);
  drawInfo(global.score, global.life);
  pacman.mapX = 14;
  pacman.mapY = 18;  
  pacman.screenX = 14 * UNIT + UNIT / 2 + OFFSET;
  pacman.screenY = 18 * UNIT + UNIT / 2 + OFFSET;
  pacman.dir = UP;
  pacman.speed = 1.2;
  drawPacman((int)pacman.screenX, (int)pacman.screenY, pacman.dir);
  for (i = 0; i < 3; i++) {
    ghost[i].mapX = 12 + i * 2;
    ghost[i].mapY = 16;
    ghost[i].screenX = mapToscreen(ghost[i].mapX) + UNIT / 2;
    ghost[i].screenY = mapToscreen(16);
    ghost[i].dir = UP;
    ghost[i].burst = 0;
    ghost[i].speed = 0.9;
    drawGhost(i, (int)ghost[i].screenX, (int)ghost[i].screenY, ghost[i].dir, ghost[i].burst);
  }
  ghost[3].mapX = 14;
  ghost[3].mapY = 12;
  ghost[3].screenX = mapToscreen(ghost[3].mapX);
  ghost[3].screenY = mapToscreen(12) + UNIT / 2;
  ghost[3].dir = LEFT;
  ghost[3].burst = 0;
  ghost[3].speed = 0.4;
  drawGhost(3, (int)ghost[3].screenX, (int)ghost[3].screenY, ghost[3].dir, ghost[3].burst);
}

void keyPress() {
  int key,
      x = pacman.mapX,
      y = pacman.mapY;
  if (bioskey(1))
    key = bioskey(0);
  else 
    key = 0;

  switch (key) {
    case VK_LEFT:
        pacman.operation = LEFT;
        if (pacman.dir == RIGHT)
          pacman.dir = pacman.operation; //如果方向相反则立即掉头
        break;
    case VK_RIGHT:
        pacman.operation = RIGHT;
        if (pacman.dir == LEFT)
          pacman.dir = pacman.operation;
        break;
    case VK_UP:
        pacman.operation = UP;
        if (pacman.dir == DOWN)
          pacman.dir = pacman.operation;
        break;
    case VK_DOWN:
        pacman.operation = DOWN;
        if (pacman.dir == UP)
          pacman.dir = pacman.operation;
        break;
    case VK_ESC:
        global.gameover = 1;
  }
}

void handleUp() {
  if (map[pacman.mapY - 1][pacman.mapX] == 0 && pacman.screenY <= mapToscreen(pacman.mapY) + UNIT / 2) {
    pacman.screenY = mapToscreen(pacman.mapY) + UNIT / 2;
    return;
  }
  pacman.screenY -= pacman.speed;
  if (pacman.screenY < mapToscreen(pacman.mapY))
    pacman.mapY--;
}

void handleDown() {
  if (map[pacman.mapY + 1][pacman.mapX] == 0 && pacman.screenY >= mapToscreen(pacman.mapY) + UNIT / 2) {
    pacman.screenY = mapToscreen(pacman.mapY) + UNIT / 2;
    return;
  }
  pacman.screenY += pacman.speed;
  if (pacman.screenY > mapToscreen(pacman.mapY + 1))
    pacman.mapY++;
}

void handleLeft() {
  if (map[pacman.mapY][pacman.mapX - 1] == 0 && pacman.screenX <= mapToscreen(pacman.mapX) + UNIT / 2) {
    pacman.screenX = mapToscreen(pacman.mapX) + UNIT / 2;
    return;
  }
  pacman.screenX -= pacman.speed;
  if (pacman.screenX < mapToscreen(pacman.mapX))
    pacman.mapX--;
}

void handleRight() {
  if (map[pacman.mapY][pacman.mapX + 1] == 0 && pacman.screenX >= mapToscreen(pacman.mapX) + UNIT / 2) {
    pacman.screenX = mapToscreen(pacman.mapX) + UNIT / 2;
    return;
  }
  pacman.screenX += pacman.speed;
  if (pacman.screenX > mapToscreen(pacman.mapX + 1))
    pacman.mapX++;
}

void changeDir() {
  if ((int)pacman.screenX == mapToscreen(pacman.mapX) + UNIT / 2 && (int)pacman.screenY == mapToscreen(pacman.mapY) + UNIT / 2)
  switch (pacman.operation) {
    case UP:
        if (map[pacman.mapY - 1][pacman.mapX] != 0)
          pacman.dir = pacman.operation;
        break;
    case DOWN:
        if (map[pacman.mapY + 1][pacman.mapX] != 0)
          pacman.dir = pacman.operation;
        break;
    case LEFT:
        if (map[pacman.mapY][pacman.mapX - 1] != 0)
          pacman.dir = pacman.operation;
        break;
    case RIGHT:
        if (map[pacman.mapY][pacman.mapX + 1] != 0)
          pacman.dir = pacman.operation;
        break;
  }
}

void pacmanRound() {
  switch (pacman.dir) {
    case UP:
        if (map[pacman.mapY + 1][pacman.mapX] != 0)
          clearPerson(map, pacman.mapX, pacman.mapY + 1);
        clearPerson(map, pacman.mapX, pacman.mapY);
        handleUp();
        break;
    case DOWN:
        if (map[pacman.mapY - 1][pacman.mapX] != 0)
          clearPerson(map, pacman.mapX, pacman.mapY - 1);
        clearPerson(map, pacman.mapX, pacman.mapY);
        handleDown();
        break;
    case LEFT:
        if (map[pacman.mapY][pacman.mapX + 1] != 0)
          clearPerson(map, pacman.mapX + 1, pacman.mapY);
        clearPerson(map, pacman.mapX, pacman.mapY);
        handleLeft();
        break;
    case RIGHT:
        if (map[pacman.mapY][pacman.mapX - 1] != 0)
          clearPerson(map, pacman.mapX - 1, pacman.mapY);
        clearPerson(map, pacman.mapX, pacman.mapY);
        handleRight();
        break;
  }
  changeDir();
  drawPacman((int)pacman.screenX, (int)pacman.screenY, pacman.dir);
}


void handleGhostUp(int i) {
  if (map[ghost[i].mapY - 1][ghost[i].mapX] == 0 && ghost[i].screenY <= mapToscreen(ghost[i].mapY) + UNIT / 2) {
    ghost[i].screenY = mapToscreen(ghost[i].mapY) + UNIT / 2;
    return;
  }
  ghost[i].screenY -= ghost[i].speed;
  if (ghost[i].screenY < mapToscreen(ghost[i].mapY))
    ghost[i].mapY--;
}

void handleGhostDown(int i) {
  if (map[ghost[i].mapY + 1][ghost[i].mapX] == 0 && ghost[i].screenY >= mapToscreen(ghost[i].mapY) + UNIT / 2) {
    ghost[i].screenY = mapToscreen(ghost[i].mapY) + UNIT / 2;
    return;
  }
  ghost[i].screenY += ghost[i].speed;
  if (ghost[i].screenY > mapToscreen(ghost[i].mapY + 1))
    ghost[i].mapY++;
}

void handleGhostLeft(int i) {
  if (map[ghost[i].mapY][ghost[i].mapX - 1] == 0 && ghost[i].screenX <= mapToscreen(ghost[i].mapX) + UNIT / 2) {
    ghost[i].screenX = mapToscreen(ghost[i].mapX) + UNIT / 2;
    return;
  }
  ghost[i].screenX -= ghost[i].speed;
  if (ghost[i].screenX < mapToscreen(ghost[i].mapX))
    ghost[i].mapX--;
}

void handleGhostRight(int i) {
  if (map[ghost[i].mapY][ghost[i].mapX + 1] == 0 && ghost[i].screenX >= mapToscreen(ghost[i].mapX) + UNIT / 2) {
    ghost[i].screenX = mapToscreen(ghost[i].mapX) + UNIT / 2;
    return;
  }
  ghost[i].screenX += ghost[i].speed;
  if (ghost[i].screenX > mapToscreen(ghost[i].mapX + 1))
    ghost[i].mapX++;
}

void changeGhostDir(int index) {
  int dir[4];
  int i;
  int flag = 0;
  if ((int)ghost[index].screenX == mapToscreen(ghost[index].mapX) + UNIT / 2 && (int)ghost[index].screenY == mapToscreen(ghost[index].mapY) + UNIT / 2) {
    /* 判断前方是否是死路
    */
    switch (ghost[index].dir) {
      case UP:
          if (map[ghost[index].mapY - 1][ghost[index].mapX] == 0)
            flag++;
          break;
      case DOWN:
          if (map[ghost[index].mapY + 1][ghost[index].mapX] == 0)
            flag++;
          break;
      case LEFT:
          if (map[ghost[index].mapY][ghost[index].mapX - 1] == 0)
            flag++;
          break;
      case RIGHT:
          if (map[ghost[index].mapY][ghost[index].mapX + 1] == 0)
            flag++;
          break;
    }
    /* 判断是否是路口
    */

    if (map[ghost[index].mapY - 1][ghost[index].mapX] != 0)
      flag++;
    if (map[ghost[index].mapY + 1][ghost[index].mapX] != 0)
      flag++;
    if (map[ghost[index].mapY][ghost[index].mapX - 1] != 0)
      flag++;
    if (map[ghost[index].mapY][ghost[index].mapX + 1] != 0)
      flag++;

    if (flag) {
      coord ghostPos[4];
      for (i = 0; i < 4; i++)
      {
        ghostPos[i].x = ghost[i].mapX;
        ghostPos[i].y = ghost[i].mapY;
        dir[i] = ghost[i].dir;
      }
      ghost[index].dir = moveAI(&ghost[index].ai, map, ghostPos, dir, pacman.mapX, pacman.mapY, ghost[index].burst);
    } 
  }
}

void ghostRound() {
  int i;
  for (i = 0; i < 4; i++) {
    switch (ghost[i].dir) {
    case UP:
        if (map[ghost[i].mapY + 1][ghost[i].mapX] != 0)
          clearPerson(map, ghost[i].mapX, ghost[i].mapY + 1);
        clearPerson(map, ghost[i].mapX, ghost[i].mapY);
        handleGhostUp(i);
        break;
    case DOWN:
        if (map[ghost[i].mapY - 1][ghost[i].mapX] != 0)
          clearPerson(map, ghost[i].mapX, ghost[i].mapY - 1);
        clearPerson(map, ghost[i].mapX, ghost[i].mapY);
        handleGhostDown(i);
        break;
    case LEFT:
        if (map[ghost[i].mapY][ghost[i].mapX + 1] != 0)
          clearPerson(map, ghost[i].mapX + 1, ghost[i].mapY);
        clearPerson(map, ghost[i].mapX, ghost[i].mapY);
        handleGhostLeft(i);
        break;
    case RIGHT:
        if (map[ghost[i].mapY][ghost[i].mapX - 1] != 0)
          clearPerson(map, ghost[i].mapX - 1, ghost[i].mapY);
        clearPerson(map, ghost[i].mapX, ghost[i].mapY);
        handleGhostRight(i);
        break;
    }
    changeGhostDir(i);
    drawGhost(i, (int)ghost[i].screenX, (int)ghost[i].screenY, ghost[i].dir, ghost[i].burst);
    if (ghost[i].burst) {
      ghost[i].burst--;
    }
  }
}

void burstChange() {
  int i;
  for (i = 0; i < 4; i++) {
    switch (ghost[i].dir) {
      case LEFT:
          ghost[i].dir = RIGHT; //如果方向相反则立即掉头
        break;
      case RIGHT:
          ghost[i].dir = LEFT;
        break;
      case UP:
          ghost[i].dir = DOWN;
        break;
      case DOWN:
          ghost[i].dir = UP;
        break;
    }
  }
}

void eventHandler() {
  int i, j;
  /* 判定吃豆豆事件
  */
  if (map[pacman.mapY][pacman.mapX] == 1) {
    global.score += 10;
    global.dou--;
    map[pacman.mapY][pacman.mapX] = 2;
    drawInfo(global.score, global.life);
  }
  /* 判断吃救命豆事件
  */
  if (map[pacman.mapY][pacman.mapX] == 3) {
    global.score += 15;
    global.dou--;
    map[pacman.mapY][pacman.mapX] = 2;
    for (i = 0; i < 4; i++) {
      ghost[i].burst = 1200;
    }
    burstChange();
    drawInfo(global.score, global.life);
  }
  /* 判定 Ghost 相关事件
  */
  for (i = 0; i < 4; i++) {
    if (pacman.mapX == ghost[i].mapX && pacman.mapY == ghost[i].mapY) {
      if (ghost[i].burst == 0) {
        global.life--;
        if (global.life == 0)
          return;
        gameInitial();
      }
      else {
        global.score += 400;
        ghost[i].mapX = 12 + i * 2;
        ghost[i].mapY = 16;
        ghost[i].screenX = (12 + i * 2) * UNIT + UNIT / 2 + OFFSET;
        ghost[i].screenY = 16 * UNIT + UNIT / 2 + OFFSET;
        ghost[i].dir = UP;
        ghost[i].burst = 0;
        drawInfo(global.score, global.life);
      }
    }

    if (ghost[i].mapY == 15) {
      switch (ghost[i].mapX) {
        case 0:
            clearPerson(map, ghost[i].mapX, ghost[i].mapY);
            clearPerson(map, ghost[i].mapX + 1, ghost[i].mapY);
            ghost[i].mapX = 26;
            ghost[i].screenX = mapToscreen(26) + UNIT / 2;
            break;
        case 27:
            clearPerson(map, ghost[i].mapX, ghost[i].mapY);
            clearPerson(map, ghost[i].mapX - 1, ghost[i].mapY);
            ghost[i].mapX = 1;
            ghost[i].screenX = mapToscreen(1) + UNIT / 2;
            break;
      }
    }
  }
  /* 判定是否在 15 特殊行
  */
  if (pacman.mapY == 15) {
    switch (pacman.mapX) {
      case 0:
          clearPerson(map, pacman.mapX, pacman.mapY);
          clearPerson(map, pacman.mapX + 1, pacman.mapY);
          pacman.mapX = 26;
          pacman.screenX = mapToscreen(26) + UNIT / 2;
          break;
      case 27:
          clearPerson(map, pacman.mapX, pacman.mapY);
          clearPerson(map, pacman.mapX - 1, pacman.mapY);
          pacman.mapX = 1;
          pacman.screenX = mapToscreen(1) + UNIT / 2;
          break;
    }
  }

  if (global.dou == 0) {
    global.dou = 308;
    for (i = 0; i < MAP_HEIGHT; i++)
      for (j = 0; j < MAP_WIDTH; j++)
        map[i][j] = mapOrigin[i][j];
    gameInitial();
    pacman.speed *= 2;
    for (i = 0; i < 4; i++)
      ghost[i].speed *= 3;
  }

  if (global.life < 0)
    global.gameover = 1;
}

void process() {
  static int timeCounter = 0,
             actionFlag = 0;

  if (timeCounter % 1000 == 0) {
    _active_page = _back_page;
    pacmanRound();
    ghostRound();
    eventHandler();

  /* test code

    setcolor(EGA_BLACK);
    _fill_color = BLACK;
    bar(0,0,300,20);
    floodfill(10,10,BLACK);
    setcolor(GREEN);
    settextstyle(1,0,6);
    outtextxy(20,3,numToString(pacman.mapX));
    outtextxy(70,3,numToString(pacman.mapY));
    outtextxy(90,3,numToString(map[pacman.mapY][pacman.mapX - 1]));
    outtextxy(120,3,numToString(pacman.screenX));
    outtextxy(170,3,numToString(pacman.screenY));
  /* test code End
  */
    timeCounter = (timeCounter + 1) % 10000;
    setvisualpage(_back_page);
  }
  else 
    timeCounter = (timeCounter + 1) % 10000;
}

int main() {
  int mode, i;
  mode = welcomePage();
  global.score = 0;
  global.life = 3;
  global.gameover = 0;
  global.dou = 308;
  gameInitial();

  /* initialize ai
  */
  if (mode == 0) {
    for (i = 0; i < 4; i++)
      foolConstruct(&ghost[i].ai, ghost[i].speed, pacman.speed, i);
  }
  else if (mode == 1) {
    for (i = 0; i < 4; i++)
      normalConstruct(&ghost[i].ai, ghost[i].speed, pacman.speed, i);
  }
  else if (mode == 2) {
    for (i = 0; i < 4; i++)
      normalConstruct(&ghost[i].ai, ghost[i].speed, pacman.speed, i);
  }

	while(1) {
    keyPress();
    process(); 
    if (global.gameover) {
      gameOverPage(global.score);
      break;
    }          
  }
  text_mode();
}