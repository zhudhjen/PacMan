#ifndef _COORD_H_
#define _COORD_H_

#include "var.h"

typedef struct {
    int x,y;
} coord;

int tp(coord pos)
{
	return pos.y * MAP_WIDTH + pos.x;
}

coord newCoord(int nx, int ny)
{
	coord pos;
	pos.x = nx;
	pos.y = ny;
	return pos;
}

coord coordMove(coord pos, int direction)
{
    int tx = (pos.x + MAP_WIDTH + dx[direction]) % MAP_WIDTH;
    int ty = (pos.y + MAP_HEIGHT + dy[direction]) % MAP_HEIGHT;
	return newCoord( tx, ty );
}

#endif /* _COORD_H_ */
