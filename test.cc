#include "coordinate-node.h"
#include "game-map.h"
#include "Axx.h"
#include <iostream>

int16_t data[] = {
    0, 1, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 1, 0, 1, 0, 1,
	1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
	0, 0, 0, 1, 0, 0, 0, 1, 0, 1,
	0, 1, 0, 1, 1, 1, 1, 1, 0, 1,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	0, 0, 0, 0, 1, 0, 0, 0, 1, 0,
	1, 1, 0, 0, 1, 0, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 0, 1, 0,
};
int main()
{
    CoordinateNode start;
    CoordinateNode end;
    end.value_.coordinate_.x_ = 9;
    end.value_.coordinate_.y_ = 9;

    GameMap map(data, 10, 10);
    Axx axx(map);
    
    axx.GetPath(start, end);
    return 0;
}