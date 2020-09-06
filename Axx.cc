#include "Axx.h"

#include <iostream>
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
    AxxNode start(s);
    AxxNode end(e);
    std::priority_queue<AxxNode> openList;
    std::unordered_map<CoordinateNode, AxxNode> nodes = {{s, start}, {e, end}};
    openList.emplace(start);
    bool reachEnd = false;
    while (!openList.empty()) {
        auto node = openList.top();
        auto pnode = nodes.find(node.node_);
        auto neighbours = map_.GetNeighbours(node.node_);
        auto costed = map_.GetCost(node.node_);
        for (auto& neighbour : neighbours) {
            AxxNode n(neighbour);
            auto pn = nodes.find(n.node_);
            if (pn == nodes.end() || pn->second.status_ != AxxNode::IN_CLOSELIST) {
                n.h_ = pnode->second.h_ + costed;
                n.g_ = map_.GetDistance(neighbour, e);
                openList.push(n);
                nodes[n.node_] = n;
                if (neighbour == e) {
                    reachEnd = true;
                    break;
                }
                if (reachEnd) {
                    break;
                }
            }
        }
        pnode->second.status_ = AxxNode::IN_CLOSELIST;
             
        openList.pop();
    }
    auto itr = nodes.find(e);
    if (itr != nodes.end()) {
        
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

int main()
{
    CoordinateNode node1, node2;

    std::cout << "node1 value:" << node1.value_.pos_ << ", node value:" << node2.value_.pos_ << std::endl;
    if (node1 == node2) {
        std::cout << "node1 = node2" << std::endl;
        std::cout << "node1 x:" << node1.value_.coordinate_.x_ << ", y:" << node1.value_.coordinate_.y_ << std::endl;
    }
    node1.value_.coordinate_.x_ = 2;
    node2.value_.coordinate_.x_ = 2;


    if (node1 == node2) {
        std::cout << "node1 = node2" << std::endl;
    }

    std::cout << "size of coordinate is " << sizeof(node1) << std::endl;
    return 0;
}