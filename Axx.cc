#include "Axx.h"

#include <iostream>
#include <queue>
#include <unordered_map>


#include "coordinate-node.h"
#include "game-map.h"

Axx::Axx(GameMap& map, BlockAllocator& allocator) : map_(map)
{
    allocator_ = &allocator;
}

Axx::~Axx()
{}

std::vector<CoordinateNode> Axx::GetPath(CoordinateNode s, CoordinateNode e)
{
    std::vector<CoordinateNode> path;

    if (!mapChanged_) {
        
    }

    AxxNode *start = new(allocator_->allocate(sizeof(AxxNode))) AxxNode(s);
    
    std::vector<AxxNode*> openList;
    
    openList.push_back(start);
    bool reachEnd = false;
    AxxNode *n = nullptr;
    while (!openList.empty()) {
        std::make_heap(openList.begin(), openList.end(),[](const AxxNode *a, const AxxNode *b)->bool
        {
            return a->f() > b->f();
        });
        std::pop_heap(openList.begin(), openList.end(), [](const AxxNode *a, const AxxNode *b)->bool
        {
            return a->f() > b->f();
        });
        auto node = openList.back();
        openList.pop_back();
        
        auto neighbours = map_.GetNeighbours(node->node_);
        auto costed = map_.GetCost(node->node_);
        for (auto& neighbour : neighbours) {
            n = new(allocator_->allocate(sizeof(AxxNode))) AxxNode(neighbour);
            map_.pathFlags_[neighbour.value_.coordinate_.x_ + neighbour.value_.coordinate_.y_ * map_.width_] = true;
            n->parent_ = node;
            
            n->h_ = node->h_ + costed;

            n->g_ = map_.GetDistance(neighbour, e);
            if (neighbour == e) {
                reachEnd = true;
                break;
            }
            openList.push_back(n);
        }        
        if (reachEnd) {
            break;
        }            
    }
    
    while (n->parent_ != nullptr) {
        path.push_back(n->node_);
        n = n->parent_;
    }
    mapChanged_ = false; // 运算完一次后，设置地图为没有变化
    return path;
}

CoordinateNode Axx::GetNextNode(CoordinateNode start, CoordinateNode end)
{
    CoordinateNode next;

    return next;
}

void Axx::RefreshMap()
{

}

void Axx::SetMapRefreshed()
{
    mapChanged_ = true;
}
