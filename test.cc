#include <iostream>

#include <sys/time.h>

#include "coordinate-node.h"
#include "game-map.h"
#include "Axx.h"

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
    BlockAllocator allocator;
    GameMap map(data, 10, 10);
    Axx axx(map, allocator);
    
    struct timeval begin, finish;
    gettimeofday(&begin, NULL);
    auto path = axx.GetPath(start, end);
    gettimeofday(&finish, NULL);
    std::cout << "get path begin:" << begin.tv_sec << "." << begin.tv_usec << ", finish:" << finish.tv_sec << "." << finish.tv_usec << std::endl;
    for (auto& step : path) {
        std::cout << "step x:" << step.value_.coordinate_.x_ << ", y:" << step.value_.coordinate_.y_ << std::endl;
    }
    std::cout << "number of steps :" << path.size() << std::endl;
    return 0;
}