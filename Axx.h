#ifndef AXX_H
#define AXX_H
#include <stdint.h>
#include <cmath>

#include <vector>

#include "blockallocator.h"
#include "game-map.h"

class GameMap;

class Axx {
public:
    explicit Axx(GameMap& map, BlockAllocator& allocator);
    void Prepare();
    ~Axx();

    std::vector<CoordinateNode> GetPath(const CoordinateNode start, const CoordinateNode end);
    CoordinateNode GetNextNode(CoordinateNode start, CoordinateNode end);
    
    void RefreshMap();
    void SetMapRefreshed();
private:
    struct AxxNode {
        explicit AxxNode(const CoordinateNode& n) : node_(n)
        {}
        AxxNode()
        {}
        CoordinateNode node_;
        AxxNode *parent_{nullptr};
        int32_t g_{0};
        int32_t h_{0};
        
        inline int32_t f() const
        {
            return g_ + h_;
        }
        inline bool operator== (const AxxNode& n) const
        {
            return node_ == n.node_;
        }
        inline bool operator< (const AxxNode& n) const
        {
            return f() > n.f();
        }
    };

    GameMap& map_; // map can be modified outside
    
    bool existPath_{false};
    bool mapChanged_{true};
    BlockAllocator *allocator_;
    std::vector<AxxNode*> nodes_;
    size_t offset_{0};
    AxxNode* GetAxxNode();
};

#endif