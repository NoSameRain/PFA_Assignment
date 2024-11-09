#pragma once
#ifndef TILE_H
#define TILE_H

#include "GamesEngineeringBase.h"

class Tile {
private:
    GamesEngineeringBase::Image image;
    bool isPassable;
public:
    Tile();
    void setUnpassable();
    const bool getIsPassable()const;
    void load(std::string filename);
    void draw(GamesEngineeringBase::Window& canvas, int x, int y);
};

#endif