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
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 4, 4, 4, 4, 4, 4, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
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
  pacman.mapX = 14;
  pacman.mapY = 18;  
  pacman.screenX = 14 * UNIT + UNIT / 2 + OFFSET;
  pacman.screenY = 18 * UNIT + UNIT / 2 + OFFSET;
  pacman.dir = UP;
  pacman.speed = 0.6;
  drawPacman((int)pacman.screenX, (int)pacman.screenY, pacman.dir);
  for (i = 0; i < 3; i++) {
    ghost[i].mapX = 12 + i * 2;
    ghost[i].mapY = 16;
    ghost[i].screenX = mapToscreen(ghost[i].mapX);
    ghost[i].screenY = mapToscreen(16);
    ghost[i].dir = UP;
    ghost[i].burst = 0;
    ghost[i].speed = 0.4;
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
  clearPerson(map, pacman.mapX, pacman.mapY);
  switch (pacman.dir) {
    case UP:
        handleUp();
        break;
    case DOWN:
        handleDown();
        break;
    case LEFT:
        handleLeft();
        break;
    case RIGHT:
        handleRight();
        break;
  }
  changeDir();
  drawPacman((int)pacman.screenX, (int)pacman.screenY, pacman.dir);
}


void handleGhostUp(int i) {
  if (map[ghost[i].mapY - 1][ghost[i].mapX] == 0 && ghost[i].screenY <= mapToscreen(ghost[i].mapY) + UNIT / 2)
    return;
  ghost[i].screenY -= ghost[i].speed;
  if (ghost[i].screenY < mapToscreen(ghost[i].mapY))
    ghost[i].mapY--;
}

void handleGhostDown(int i) {
  if (map[ghost[i].mapY + 1][ghost[i].mapX] == 0 && ghost[i].screenY >= mapToscreen(ghost[i].mapY) + UNIT / 2)
    return;
  ghost[i].screenY += ghost[i].speed;
  if (ghost[i].screenY > mapToscreen(ghost[i].mapY + 1))
    ghost[i].mapY++;
}

void handleGhostLeft(int i) {
  if (map[ghost[i].mapY][ghost[i].mapX - 1] == 0 && ghost[i].screenX <= mapToscreen(ghost[i].mapX) + UNIT / 2)
    return;
  ghost[i].screenX -= ghost[i].speed;
  if (ghost[i].screenX < mapToscreen(ghost[i].mapX))
    ghost[i].mapX--;
}

void handleGhostRight(int i) {
  if (map[ghost[i].mapY][ghost[i].mapX + 1] == 0 && ghost[i].screenX >= mapToscreen(ghost[i].mapX) + UNIT / 2)
    return;
  ghost[i].screenX += ghost[i].speed;
  if (ghost[i].screenX > mapToscreen(ghost[i].mapX + 1))
    ghost[i].mapX++;
}

void changeGhostDir(int i) {
  if ((int)ghost[i].screenX == mapToscreen(ghost[i].mapX) + UNIT / 2 && (int)ghost[i].screenY == mapToscreen(ghost[i].mapY) + UNIT / 2) {
    int flag = 0;
    switch (ghost[i].dir) {
      case UP:
          if (map[ghost[i].mapY - 1][ghost[i].mapX] != 0)
            flag++;
          break;
      case DOWN:
          if (map[ghost[i].mapY + 1][ghost[i].mapX] != 0)
            flag++;
          break;
      case LEFT:
          if (map[ghost[i].mapY][ghost[i].mapX - 1] != 0)
            flag++;
          break;
      case RIGHT:
          if (map[ghost[i].mapY][ghost[i].mapX + 1] != 0)
            flag++;
          break;
    }
    if (flag >= 3) {
      coord ghostPos;
      ghostPos.x = ghost[i].mapX;
      ghostPos.y = ghost[i].mapY;
      ghost[i].dir = moveAI(&ghost[i].ai, map, &ghostPos, &ghost[i].dir, pacman.mapX, pacman.mapY, ghost[i].burst);
    } 
  }
}

void ghostRound() {
  int i;
  for (i = 0; i < 4; i++) {
    clearPerson(map, ghost[i].mapX, ghost[i].mapY);
    switch (ghost[i].dir) {
    case UP:
        handleGhostUp(i);
        break;
    case DOWN:
        handleGhostDown(i);
        break;
    case LEFT:
        handleGhostLeft(i);
        break;
    case RIGHT:
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

void eventHandler() {
  int i;
  /* 判定吃豆豆事件
  */
  if (map[pacman.mapY][pacman.mapX] == 1) {
    global.score += 10;
    map[pacman.mapY][pacman.mapX] = 2;
  }
  /* 判断吃救命豆事件
  */
  if (map[pacman.mapY][pacman.mapX] == 3) {
    global.score += 15;
    map[pacman.mapY][pacman.mapX] = 2;
    for (i = 0; i < 4; i++) {
      ghost[i].burst = 1000;
    }
  }
  /* 判定 Ghost 与 pacman 相撞事件
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
        global.score += 200;
        ghost[i].mapX = 12 + i * 2;
        ghost[i].mapY = 16;
        ghost[i].screenX = (12 + i * 2) * UNIT + UNIT / 2 + OFFSET;
        ghost[i].screenY = 16 * UNIT + UNIT / 2 + OFFSET;
        ghost[i].dir = UP;
        ghost[i].burst = 0;
      }
    }
  }
  if (global.life == 0)
    global.gameover = 1;
}

void process() {
  static int timeCounter = 0,
             actionFlag = 0;

  if (timeCounter % 3 == 0) {
    pacmanRound();
    ghostRound();
    eventHandler();
    drawInfo(global.score, global.life);

  /* test code
  */ 
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
  }
  else 
    timeCounter = (timeCounter + 1) % 10000;
}

int main() {
  int mode, i;
  mode = welcomePage();
  global.score = 0;
  global.life = 2;
  global.gameover = 0;
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