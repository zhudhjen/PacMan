#include "ai.h"

coord queue[1000];
int depth[1000];
bool g[MAP_HEIGHT][MAP_WIDTH];

int moveAI (classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], coord *ghostPos, int *ghostDir, double pacPosX, double pacPosY, int burst)
{
    return this->move(this, map, ghostPos, ghostDir, pacPosX, pacPosY, burst);
}

bool checkDirection(int map[MAP_HEIGHT][MAP_WIDTH], coord pos, int direction)
{
    coord newPos = coordMove(pos, direction);
    if ((map[newPos.y][newPos.x] == 0)||
        (map[pos.y][pos.x] != 4 && map[newPos.y][newPos.x] == 4))
        return FALSE;
    else
        return TRUE;
}

int getDistance(int map[MAP_HEIGHT][MAP_WIDTH], coord pos, coord goal, int direction)
{
    coord cur, tmp;
    int i, j, front = 1, rear = 1;
    memset(g, 0, sizeof(g));
    memset(queue, 0, sizeof(queue));
    memset(depth, 0, sizeof(depth));

    queue[0] = coordMove(pos, direction);
    depth[0] = 1;
    g[queue[0].y][queue[0].x] = TRUE;
    g[pos.y][pos.x] = TRUE;
    for (i = 0; i < 4; ++i)
    {
        tmp = coordMove(queue[0], i);
        if (checkDirection(map, queue[0], i) && !g[tmp.y][tmp.x])
        {
            depth[rear] = 2;
            queue[rear++] = tmp;
            g[tmp.y][tmp.x] = TRUE;
            if (tmp.x == goal.x && tmp.y == goal.y)
            {
                return depth[rear - 1];
            }
        }
    }
    g[pos.y][pos.x] = FALSE;
    while(front < rear)
    {
        cur = queue[front];
        for (i = 0; i < 4; ++i)
        {
            tmp = coordMove(cur, i);
            if (checkDirection(map, cur, i) && !g[tmp.y][tmp.x])
            {
                depth[rear] = depth[front]+1;
                queue[rear++] = tmp;
                g[tmp.y][tmp.x] = TRUE;
                if (tmp.x == goal.x && tmp.y == goal.y)
                {
                    return depth[rear - 1];
                }
            }
        }
        front++;
    }
    return -1;
}
