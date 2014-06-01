#include "main.h"

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
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
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

int welcomePage() {
  int mode = 0;
  drawWelcomePage(mode);
  while (1) {
    if (bioskey(1))
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
    }
    drawWelcomePage(mode);
  }
}

void gameInitial() {
  int i;
  initMap(map);
  pacman.mapX = 14;
  pacman.mapY = 17;  
  pacman.screenX = 14 * UNIT + UNIT / 2;
  pacman.screenY = 17 * UNIT + UNIT / 2;
  pacman.dir = LEFT;
  pacman.speed = 0.6;
  drawPacman((int)pacman.screenX, (int)pacman.screenY, pacman.dir);
  for (i = 0; i < 3; i++) {
    ghost[i].mapX = 12 + i * 2;
    ghost[i].mapY = 16;
    ghost[i].screenX = (12 + i * 2) * UNIT + UNIT;
    ghost[i].screenY = 16 * UNIT + UNIT / 2;
    ghost[i].dir = UP;
    ghost[i].burst = 0;
    ghost[i].speed = 0.4;
    drawGhost(i, (int)ghost[i].screenX, (int)ghost[i].screenY, ghost[i].dir);
  }
  ghost[3].mapX = 14;
  ghost[3].mapY = 14;
  ghost[3].screenX = (12 + i * 2) * UNIT + UNIT / 2;
  ghost[3].screenY = 16 * UNIT + UNIT / 2;
  ghost[3].dir = LEFT;
  ghost[3].burst = 0;
  ghost[3].speed = 0.4;
  drawGhost(3, (int)ghost[3].screenX, (int)ghost[3].screenY, ghost[3].dir);
}

void keyPress() {
  int key,
      x = pacman.mapX;
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
  }
}

void handleUp() {
  if (map[pacman.mapX][pacman.mapY - 1] == 0 && pacman.screenY <= pacman.mapY * UNIT + UNIT / 2)
    return;
  pacman.screenY -= pacman.speed;
  if (pacman.screenY < pacman.mapY * UNIT)
    pacman.mapY--;
}

void handleDown() {
  if (map[pacman.mapX][pacman.mapY + 1] == 0 && pacman.screenY >= pacman.mapY * UNIT + UNIT / 2)
    return;
  pacman.screenY += pacman.speed;
  if (pacman.screenY > (pacman.mapY + 1) * UNIT)
    pacman.mapY++;
}

void handleLeft() {
  if (map[pacman.mapX - 1][pacman.mapY] == 0 && pacman.screenX <= pacman.mapX * UNIT + UNIT / 2)
    return;
  pacman.screenX -= pacman.speed;
  if (pacman.screenX < pacman.mapX * UNIT)
    pacman.mapX--;
}

void handleRight() {
  if (map[pacman.mapX + 1][pacman.mapY] == 0 && pacman.screenX >= pacman.mapX * UNIT + UNIT / 2)
    return;
  pacman.screenX += pacman.speed;
  if (pacman.screenX > (pacman.mapX + 1) * UNIT)
    pacman.mapX++;
}

void changeDir() {
  if ((int)pacman.screenX == pacman.mapX * UNIT + UNIT / 2 && (int)pacman.screenY == pacman.mapY * UNIT + UNIT / 2)
  switch (pacman.operation) {
    case UP:
        if (map[pacman.mapX][pacman.mapY - 1] != 0)
          pacman.dir = pacman.operation;
        break;
    case DOWN:
        if (map[pacman.mapX][pacman.mapY + 1] != 0)
          pacman.dir = pacman.operation;
        break;
    case LEFT:
        if (map[pacman.mapX - 1][pacman.mapY] != 0)
          pacman.dir = pacman.operation;
        break;
    case RIGHT:
        if (map[pacman.mapX + 1][pacman.mapY] != 0)
          pacman.dir = pacman.operation;
        break;
  }
}

void pacmanRound() {
  clearPerson(pacman.mapX, pacman.mapY, map);
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
  if (map[ghost[i].mapX][ghost[i].mapY - 1] == 0 && ghost[i].screenY <= ghost[i].mapY * UNIT + UNIT / 2)
    return;
  ghost[i].screenY -= ghost[i].speed;
  if (ghost[i].screenY < ghost[i].mapY * UNIT)
    ghost[i].mapY--;
}

void handleGhostDown(int i) {
  if (map[ghost[i].mapX][ghost[i].mapY + 1] == 0 && ghost[i].screenY >= ghost[i].mapY * UNIT + UNIT / 2)
    return;
  ghost[i].screenY += ghost[i].speed;
  if (ghost[i].screenY > (ghost[i].mapY + 1) * UNIT)
    ghost[i].mapY++;
}

void handleGhostLeft(int i) {
  if (map[ghost[i].mapX - 1][ghost[i].mapY] == 0 && ghost[i].screenX <= ghost[i].mapX * UNIT + UNIT / 2)
    return;
  ghost[i].screenX -= ghost[i].speed;
  if (ghost[i].screenX < ghost[i].mapX * UNIT)
    ghost[i].mapX--;
}

void handleGhostRight(int i) {
  if (map[ghost[i].mapX + 1][ghost[i].mapY] == 0 && ghost[i].screenX >= ghost[i].mapX * UNIT + UNIT / 2)
    return;
  ghost[i].screenX += ghost[i].speed;
  if (ghost[i].screenX > (ghost[i].mapX + 1) * UNIT)
    ghost[i].mapX++;
}

void changeGhostDir(int i) {
  if ((int)ghost[i].screenX == ghost[i].mapX * UNIT + UNIT / 2 && (int)ghost[i].screenY == ghost[i].mapY * UNIT + UNIT / 2) {
    int flag = 0;
    switch (ghost[i].dir) {
      case UP:
          if (map[ghost[i].mapX][ghost[i].mapY - 1] != 0)
            flag++;
          break;
      case DOWN:
          if (map[ghost[i].mapX][ghost[i].mapY + 1] != 0)
            flag++;
          break;
      case LEFT:
          if (map[ghost[i].mapX - 1][ghost[i].mapY] != 0)
            flag++;
          break;
      case RIGHT:
          if (map[ghost[i].mapX + 1][ghost[i].mapY] != 0)
            flag++;
          break;
    }
    if (flag >= 3) {
      coord ghostPos;
      ghostPos.x = ghost[i].mapX;
      ghostPos.y = ghost[i].mapY;
      ghost[i].dir = moveAI(&ghost[i].ai, map, ghostPos, pacman.mapX, pacman.mapY, ghost[i].burst);
    } 
  }
}

void ghostRound() {
  int i;
  for (i = 0; i < 4; i++) {
    clearPerson(ghost[i].mapX, ghost[i].mapY, map);
    switch (ghost.dir) {
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
    drawGhost(i, (int)ghost[i].screenX, (int)ghost[i].screenY, ghost[i].dir);
    if (ghost[i].burst) {
      ghost[i].burst--;
    }
  }
}

void eventHandler() {
  int i;
  /* 判定吃豆豆事件
  */
  if (map[pacman.mapX][pacman.mapY] == 1) {
    global.score += 10;
    map[pacman.mapX][pacman.mapY] = 2;
  }
  /* 判断吃救命豆事件
  */
  if (map[pacman.mapX][pacman.mapY] == 3) {
    global.score += 15;
    for (i = 0; i < 4; i++) {
      ghost[i].burst = 450;
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
        ghost[i].screenX = (12 + i * 2) * UNIT + UNIT / 2;
        ghost[i].screenY = 16 * UNIT + UNIT / 2;
        ghost[i].dir = UP;
        ghost[i].burst = 0;
      }
    }
  }
}

void process() {
  static int timeCounter = 0,
             actionFlag = 0;

  if ((inportb(0x3da)&0x08) != 0 && actionFlag == 0 && (timeCounter % 2) == 0) {
    pacmanRound();
    ghostRound();
    eventHandler();
    actionFlag = 1;
  }
  else if ((inportb(0x3da)&0x08) == 0 && actionFlag == 1) {
    actionFlag = 0;
    timeCounter++;
  }
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
      foolConstruct(ghost[i].ai, ghost[i].speed, pacman.speed, i);
  }
  else if (mode == 1) {
    for (i = 0; i < 4; i++)
      normalConstruct(ghost[i].ai, ghost[i].speed, pacman.speed, i);
  }
  else if (mode == 2) {
    for (i = 0; i < 4; i++)
      expertConstruct(ghost[i].ai, ghost[i].speed, pacman.speed, i);
  }

	while(1) {
    keyPress();
    process(); 
    if (global.gameover) {
      break;
    }          
  }
}