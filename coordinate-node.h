#ifndef COORDINATE_NODE_H
#define COORDINATE_NODE_H

#include <stdint.h>
#include <cmath>

struct CoordinateNode {
    union value
    {
        uint32_t pos_;
        struct {
            uint32_t x_ : 16;
            uint32_t y_ : 16;
        } coordinate_;
    };
    
    value value_{0};
    
    bool operator== (const CoordinateNode& node) const
    {
        return value_.pos_ == node.value_.pos_;
    }

    CoordinateNode(const CoordinateNode& n)
    {
        value_.pos_ = n.value_.pos_;
    }
    CoordinateNode(uint16_t x, uint16_t y)
    {
        value_.coordinate_.x_ = x;
        value_.coordinate_.y_ = y;
    }
    CoordinateNode()
    {}
};

namespace std {
    template<>
    struct hash<CoordinateNode> {
        size_t operator() (const CoordinateNode& node) const noexcept
        {
            return hash<uint32_t>() (node.value_.pos_);
        }
    };
}

struct CoordinateNodePair {
    union value
    {
        uint64_t pathKey_;
        struct {
            CoordinateNode start_;
            CoordinateNode end_;
        } pair_;
    };

    value value_{0};

    bool operator== (const CoordinateNodePair& pair) const
    {
        return value_.pathKey_ == pair.value_.pathKey_;
    }

    CoordinateNodePair(const CoordinateNodePair& pair)
    {
        value_.pathKey_ = pair.value_.pathKey_;
    }

    CoordinateNodePair()
    {}

};

#endif