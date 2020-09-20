#ifndef AXX_H
#define AXX_H
#include <stdint.h>
#include <cmath>

#include <vector>

#include "blockallocator.h"
#include "game-map.h"

class GameMap;

struct AxxNode {
    explicit AxxNode(const CoordinateNode& n) : node_(n)
    {}
    AxxNode()
    {}
    CoordinateNode node_;
    AxxNode *parent_{nullptr};
    int32_t g_{0};
    int32_t h_{0};
    
    int32_t f() const
    {
        return g_ + h_;
    }
    bool operator== (const AxxNode& n) const
    {
        return node_ == n.node_;
    }
    bool operator< (const AxxNode& n) const
    {
        return f() > n.f();
    }
};

class Axx {
public:
    explicit Axx(GameMap& map, BlockAllocator& allocator);
    ~Axx();

    std::vector<CoordinateNode> GetPath(CoordinateNode start, CoordinateNode end);
    CoordinateNode GetNextNode(CoordinateNode start, CoordinateNode end);
    
    void RefreshMap();
    void SetMapRefreshed();
private:
    GameMap& map_; // map can be modified outside
    
    bool existPath_{false};
    bool mapChanged_{true};
    BlockAllocator *allocator_;
};

#endif