#ifndef _COORD_H_
#define _COORD_H_

typedef struct {
    int x,y;
} coord;

coord newCoord(int nx, int ny);
coord coordMove(coord pos, int direction);

#endif /* _COORD_H_ */
