#include "World.h"
#include <iostream>
using namespace std;
using namespace GamesEngineeringBase; 

World::World(Window& canvas) {
    tileset.load("Resources/tiles.txt");

    //the maximum number of tiles drawn on the screen at the same time
    tileNumX = canvas.getWidth() / tileWidthHeight + 1;
    tileNumY = canvas.getHeight() / tileWidthHeight + 1;

    for (int i = 0; i < tileType; i++) {
        if ((i >= 14 && i <= 22) || i == 24) tiles[i].setUnpassable();
        string tilename = "Resources/" + to_string(i) + ".png";
        tiles[i].load(tilename);
    }
}

void World::draw(Window& canvas, Vec2& camPos) {
    //the number of tiles calculated from camera position
    int tileIndexX = camPos.x / tileWidthHeight;
    int tileIndexY = camPos.y / tileWidthHeight;
    int tileDrawStartX = 0;
    int tileDrawStartY = 0;
    int tileswide = tileset.getTileswide();
    int tileshigh = tileset.getTileshigh();
    int tileDrawStartOffsetY = tileWidthHeight - camPos.y % tileWidthHeight;
    int tileDrawStartOffsetX = tileWidthHeight - camPos.x % tileWidthHeight;

    for (int i = tileIndexX; i < min((tileIndexX + tileNumX), tileswide); i++) {
        for (int j = tileIndexY; j < min((tileIndexY + tileNumY), tileshigh); j++) {
            int tileNameIndex = tileset.getTileIndex(i, j);
            if (tileNameIndex == 24 || tileNameIndex == 25) {
                // draw grass tile under stone tile first(stone tile has alpha)
                tiles[0].draw(canvas, tileDrawStartX, tileDrawStartY);
            }
            tiles[tileNameIndex].draw(canvas, tileDrawStartX, tileDrawStartY);
            // adjust the starting position on the Y-axis
            if (tileDrawStartY == 0) tileDrawStartY += tileDrawStartOffsetY; // draw from pixel inside the tile png
            else tileDrawStartY += tileWidthHeight; // draw from pixel at the edge of tile png
        }
        // reset Y
        tileDrawStartY = 0;
        // adjust the starting position on the X-axis
        if (tileDrawStartX == 0) tileDrawStartX += tileDrawStartOffsetX;
        else tileDrawStartX += tileWidthHeight;
    }
}

//Check if  Player collide with impassable Tiles,
// by check if the position of 'four corners' & 'four points on the edge' & 'one point inside'
// of the Player sprite are inside the impassable tiles
bool World::checkTilePassable(int x, int y) { 
    int leftX = x;
    int topY = y;
    int rightX = x + playerSpriteSize;
    int bottomY = y + playerSpriteSize;

    for (int i = leftX; i <= rightX; i = i+ playerSpriteSize / 2)
        for (int j = topY; j <= bottomY; j = j + playerSpriteSize / 2) {
            int tileIndex = tileset.getTileIndex(i / tileWidthHeight, j / tileWidthHeight);
            if (!tiles[tileIndex].getIsPassable()) return false;
        }
    return true;
  
}
