#ifndef AXX_H
#define AXX_H
#include <stdint.h>
#include <cmath>
#include <queue>
#include <vector>
#include <unordered_map>

#include "game-map.h"
class GameMap;
struct AxxNode;

class Axx {
public:
    explicit Axx(const GameMap& map);
    ~Axx();

    std::vector<CoordinateNode> GetPath(CoordinateNode start, CoordinateNode end);
    CoordinateNode GetNextNode(CoordinateNode start, CoordinateNode end);
    
    void RefreshMap();
    void SetMapRefreshed();
private:
    const GameMap& map_; // map can be modified outside
    
    bool existPath_{false};
    bool mapChanged_{true};
    std::priority_queue<AxxNode> openList_;
    std::unordered_map<CoordinateNode, AxxNode> nodes_;
    
};

struct AxxNode {
    explicit AxxNode(const CoordinateNode& n)
    {
        node_ = n;
    }
    CoordinateNode node_;
    CoordinateNode parent_;
    int32_t g_{0};
    int32_t h_{0};
    enum {
        NOEXIST,
        IN_OPENLIST,
        IN_CLOSELIST
    } status_{NOEXIST};
    int32_t f() const
    {
        return g_ + h_;
    }
    bool operator== (const AxxNode& n)
    {
        return node_ == n.node_;
    }
    bool operator< (const AxxNode& n)
    {
        return f() > n.f();
    }
};

#endif