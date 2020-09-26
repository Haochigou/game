#include "game-map.h"

#include <iostream>
#include <climits>
#include <string.h>

const std::array<std::pair<int, int>, 8> GameMap::directions_ = {
    std::make_pair(0, -1), std::make_pair(0, 1), std::make_pair(1, 0), std::make_pair(-1, 0), 
    std::make_pair(1, 1), std::make_pair(-1, -1), std::make_pair(1, -1), std::make_pair(-1, 1)
};

int  GameMap::GetCost(const CoordinateNode node) const
{
    return 1;
}

int  GameMap::GetDistance(const CoordinateNode start, const CoordinateNode end) const
{
    int deltaX = std::abs((int)start.value_.coordinate_.x_ - (int)end.value_.coordinate_.x_);
    int deltaY = std::abs((int)start.value_.coordinate_.y_ - (int)end.value_.coordinate_.y_);
    return deltaX > deltaY ? deltaX : deltaY;
}

void GameMap::ResetFlags()
{
    std::vector<bool> flags(width_ * height_, false);
    pathFlags_.swap(flags);
    
}

int GameMap::GetCanPassBlockNum() const
{
    int cnt = 0;
    if (!originData_) {
        for (uint16_t y = 0; y < height_; ++y) {
            for (uint16_t x = 0; x < width_; ++x) {
                if (CanPass(CoordinateNode(x, y))) {
                    ++cnt;
                }
            }
        }
    }
    return cnt;
}

bool GameMap::CanPass(const CoordinateNode node) const
{    
    return currentData_[node.value_.coordinate_.y_ * width_ + node.value_.coordinate_.x_] == 0;
}

std::vector<CoordinateNode> GameMap::GetNeighbours(const CoordinateNode node) const
{
    std::vector<CoordinateNode> neighbours;
    
    for (auto& direction : directions_) {
        CoordinateNode neighbour = node;
        neighbour.value_.coordinate_.x_ += direction.first;
        neighbour.value_.coordinate_.y_ += direction.second;

        if (neighbour.value_.coordinate_.x_ < width_ &&
            neighbour.value_.coordinate_.y_ < height_ &&            
            CanPass(neighbour) && 
            !pathFlags_[neighbour.value_.coordinate_.x_ + neighbour.value_.coordinate_.y_ * width_])
        {            
            neighbours.push_back(neighbour);
        }
    }

    return neighbours;
}

GameMap::GameMap(const int16_t *data, const uint16_t width, const uint16_t height) 
    : originData_(data), width_(width), height_(height)
{
    if (width_ < INT16_MAX && height_ < INT16_MAX && originData_) {
        currentData_ = (int16_t *)malloc((uint32_t)width_ * height_ * sizeof(int16_t));
        if (currentData_) {
            memcpy(currentData_, originData_, (uint32_t)width_ * height_ * sizeof(int16_t));
            for (int i = 0; i < height_; ++i) {
                for (int j = 0; j < width_; ++j) {
                    std::cout << currentData_[i * width_ + j] << ",";
                }
                std::cout << std::endl;
            }
            ResetFlags();
        }
    }
}

GameMap::GameMap(GameMap&& map) : originData_(map.originData_), width_(map.width_), height_(map.height_)
{
    if (width_ < INT16_MAX && height_ < INT16_MAX && !originData_) {
        currentData_ = (int16_t *)malloc((uint32_t)width_ * height_ * sizeof(int16_t));
        if (currentData_) {
            memcpy(currentData_, originData_, (uint32_t)width_ * height_ * sizeof(int16_t));
            ResetFlags();
        }
    }
}

GameMap::~GameMap()
{
    if (!currentData_) {
        free(currentData_);
    }    
}

void GameMap::AddObsever(Axx& axx)
{
    axxObservers_.push_back(&axx);
}

void GameMap::Notify()
{
    for (auto& axx : axxObservers_) {
        axx->SetMapRefreshed();
    }
}

void GameMap::Update(const CoordinateNode node, const int16_t value)
{
    currentData_[(uint32_t)node.value_.coordinate_.y_ * width_ + node.value_.coordinate_.x_] = value;
}

void GameMap::Update(const std::vector<std::pair<CoordinateNode, int16_t>>& values)
{
    for (auto& value : values) {
        Update(value.first, value.second);
    }
}

void GameMap::Repaint(const std::vector<std::pair<CoordinateNode, int16_t>>& values)
{
    if (!currentData_) {
        memcpy(currentData_, originData_, (uint32_t)width_ * height_ * sizeof(int16_t));
        Update(values);
    }
}
