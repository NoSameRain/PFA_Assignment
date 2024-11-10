#pragma once
#ifndef WORLD_H
#define WORLD_H

#include "Tileset.h"
#include "Tile.h"
#include "Constants.h"
#include "GamesEngineeringBase.h"
#include "Utils.h"  

class World {
private:
    int tileNumX = 33; //draw up to 32+1 tiles
    int tileNumY = 25; //draw up to 24+1 tiles
    Tileset tileset;
    static const int tileType = 26;
    Tile tiles[tileType]; //store 26 diff tile objects

public:
    World(GamesEngineeringBase::Window& canvas);
    //const Tileset& getTileset()const;
    //const Tile& getTile(int i)const;
    void draw(GamesEngineeringBase::Window& canvas, Vec2& camPos);
    bool checkTilePassable(int x, int y);
};

#endif
