#include "Axx.h"

#include <iostream>
#include <queue>
#include <unordered_map>

#include "coordinate-node.h"
#include "game-map.h"

Axx::Axx(const GameMap& map) : map_(map)
{}

Axx::~Axx()
{}

std::vector<CoordinateNode> Axx::GetPath(CoordinateNode s, CoordinateNode e)
{
    std::vector<CoordinateNode> path;

    if (!mapChanged_) {
        
    }


    AxxNode *start = new AxxNode(s);
    AxxNode *end = new AxxNode(e);
    std::priority_queue<AxxNode> openList;
    std::unordered_map<CoordinateNode, AxxNode *> nodes = {{s, start}, {e, end}};
    openList.push(*start);
    bool reachEnd = false;
    while (!openList.empty()) {
        auto node = openList.top();
        auto pnode = nodes.find(node.node_);
        auto neighbours = map_.GetNeighbours(node.node_);
        auto costed = map_.GetCost(node.node_);
        for (auto& neighbour : neighbours) {
            AxxNode *n = new AxxNode(neighbour);
            n->parent_ = nodes.find(pnode->first)->second;
            auto pn = nodes.find(n->node_);
            if (pn == nodes.end() || pn->second->status_ != AxxNode::IN_CLOSELIST) {
                n->h_ = node.h_ + costed;
                n->g_ = map_.GetDistance(neighbour, e);
                openList.push(*n);
                nodes[n->node_] = n;
                if (neighbour == e) {
                    reachEnd = true;
                    break;
                }
                if (reachEnd) {
                    break;
                }
            }
        }
        pnode->second->status_ = AxxNode::IN_CLOSELIST;
        
        openList.pop();
    }
    auto itr = nodes.find(e);
    if (itr != nodes.end()) {
        auto en = itr->second;
        while (!(en->node_ == s)) {
            path.push_back(en->node_);
            en = en->parent_;
        }

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
