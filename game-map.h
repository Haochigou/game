#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <stdint.h>
#include <vector>
#include <array>
#include <list>

#include "coordinate-node.h"
#include "Axx.h"

class Axx;

class GameMap {
public:
    GameMap(const int16_t *data, const uint16_t width, const uint16_t height);
    GameMap(GameMap&& map);
    ~GameMap();

    friend class Axx;

    /*
     * 更新当前地图上的元素
     */
    void Update(const CoordinateNode node, const int16_t value);
    void Update(const std::vector<std::pair<CoordinateNode, int16_t>>& values);
    /*
     * 在初始地图的基础上，根据输入值重绘地图
     */
    void Repaint(const std::vector<std::pair<CoordinateNode, int16_t>>& values);
    /*  
     * 由地图定义坐标点之间的距离，可以选择斜角距离、曼哈顿距离或者其他
     */
    int  GetDistance(const CoordinateNode start, const CoordinateNode end) const;
    bool CanPass(const CoordinateNode node) const;
    int  GetCost(const CoordinateNode node) const;
    std::vector<CoordinateNode> GetNeighbours(const CoordinateNode node) const;
    
    int GetCanPassBlockNum() const;
    
private:
    void AddObsever(Axx& axx);
    void Notify();
    void ResetFlags();
    //void SetPath(const CoordinateNode node);
    static const std::array<std::pair<int, int>, 8> directions_;
    
private:
    int16_t *currentData_{nullptr};
    const int16_t *originData_{nullptr};
    std::vector<bool> pathFlags_;
    uint16_t width_{0};
    uint16_t height_{0};
    std::list<Axx*> axxObservers_;
};

#endif