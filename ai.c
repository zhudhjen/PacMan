#include "ai.h"

coord queue[1000];
int depth[1000];
bool g[MAP_HEIGHT][MAP_WIDTH];

//call the function pointer which is initialized by the certain constructor
int moveAI (classAI *this, int map[MAP_HEIGHT][MAP_WIDTH], coord *ghostPos, int *ghostDir, double pacPosX, double pacPosY, int burst)
{
    return this->move(this, map, ghostPos, ghostDir, pacPosX, pacPosY, burst);
}

//check whether the given direction can be walked through
bool checkDirection(int map[MAP_HEIGHT][MAP_WIDTH], coord pos, int direction)
{
    coord newPos = coordMove(pos, direction);
    printf("checking: (%d, %d) %d", pos.x, pos.y, direction);
    if ((map[newPos.y][newPos.x] == 0)||
        (map[pos.y][pos.x] != 4 && map[newPos.y][newPos.x] == 4))
        printf(": FALSE\n");
        return FALSE;
    else
        return TRUE;
}

//get the distance from pos to goal from the given direction
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

//calculate the weighted distance of points of a given type in a given range
int countWeightedElement(int dep, int map[MAP_HEIGHT][MAP_WIDTH], coord pos, int range, int type)
{
    int i, tx, ty, count = 0;
    coord tpos;
    if (map[pos.y][pos.x] == type)
        count = 1;
    if (dep == 0)
    {
        memset(g, 0, sizeof(g));
        g[pos.y][pos.x] = TRUE;
    }
    if (dep == range)
        return count;
    for (i = 0; i < 4; ++i)
    {
        tpos = coordMove(pos, i);
        if (!g[tpos.y][tpos.x] && checkDirection(map, pos, i))
        {
            g[tpos.y][tpos.x] = TRUE;
            count += countElement(dep + 1, map, tpos, range, type);
        }
    }
    return count;
}

