#pragma once
#ifndef TILESET_H
#define TILESET_H
#include "GamesEngineeringBase.h"

class Tileset {
private:
    int tileswide;
    int tileshigh;
    int tilewidth;
    int tileheight;
    int layer;
    int** arr2D;
public:
    Tileset();
    int getTileswide() const;
    int getTileshigh() const;
    void load(std::string filename);
    const int getTileIndex(int i, int j)const;
};

#endif