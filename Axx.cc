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
{
    if (!nodes_.empty()) {
        for (auto& node : nodes_) {
            allocator_->free(node, sizeof(AxxNode));
        }
    }
}

void Axx::Prepare()
{
    int all = map_.GetCanPassBlockNum();    
    
    for (int i = 0; i < all - nodes_.size(); ++i) {
        nodes_.push_back(new(allocator_->allocate(sizeof(AxxNode))) AxxNode());
    }

    offset_ = 0;
}

std::vector<CoordinateNode> Axx::GetPath(const CoordinateNode s, const CoordinateNode e)
{
    std::vector<CoordinateNode> path;

    offset_ = 0;
    if (!mapChanged_) {
        
    }

    AxxNode *start = new(allocator_->allocate(sizeof(AxxNode))) AxxNode(s);
    
    std::vector<AxxNode*> openList;
    
    openList.push_back(start);
    bool reachEnd = false;
    AxxNode *n = nullptr;
    while (!openList.empty()) {
        auto CompareAxxNode = [](const AxxNode* a, const AxxNode* b)
        {
            return a->f() > b->f();
        };
        std::make_heap(openList.begin(), openList.end(),CompareAxxNode);
        std::pop_heap(openList.begin(), openList.end(), CompareAxxNode);
        auto node = openList.back();
        openList.pop_back();
        
        auto neighbours = map_.GetNeighbours(node->node_);
        auto costed = map_.GetCost(node->node_);
        for (auto& neighbour : neighbours) {
            n = GetAxxNode();
            /*
            if (nodes_.empty()) {
                n = new(allocator_->allocate(sizeof(AxxNode))) AxxNode();
            } else {
                n = nodes_[offset_++];
            }
            */
            n->node_ = neighbour;
            map_.pathFlags_[neighbour.value_.coordinate_.x_ + neighbour.value_.coordinate_.y_ * map_.width_] = true;
            n->parent_ = node;
            
            n->h_ = node->h_ + costed;

            n->g_ = map_.GetDistance(neighbour, e);
            if (neighbour == e) {
                openList.clear();
                break;
            }
            openList.push_back(n);
        }          
    }
    
    while (n != nullptr && n->parent_ != nullptr) {
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

inline Axx::AxxNode* Axx::GetAxxNode()
{
    if (offset_ == nodes_.size()) {        
        nodes_.push_back(new(allocator_->allocate(sizeof(AxxNode))) AxxNode());
    }
    return nodes_[offset_++];
}