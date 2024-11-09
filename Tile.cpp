#include "Tile.h"
using namespace std;
using namespace GamesEngineeringBase;

Tile::Tile() {
    isPassable = true;
}
void Tile::setUnpassable() {
    isPassable = false;
}
const bool Tile::getIsPassable() const{
    return isPassable;
}
void Tile::load(string filename) {
    image.load(filename);
    //cout << filename << endl;
}
void Tile::draw(Window& canvas, int x, int y) { //screen x y
    //cout << x << " " << y << endl;
    for (unsigned int i = 0; i < image.width; i++) {
        if (x + i >= 0 && x + i < canvas.getWidth()) {
            for (unsigned int j = 0; j < image.height; j++) {
                if (y + j >= 0 && y + j < canvas.getHeight()) {
                    if (image.alphaAt(i, j) > 200)
                        canvas.draw(x + i, y + j, image.at(i, j));
                }
            }
        }
    }
}