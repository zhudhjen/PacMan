#include "var.h"
#include "coord.h"

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
