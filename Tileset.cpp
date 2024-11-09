#include "Tileset.h"
#include <fstream>
#include <iostream>
using namespace std;
using namespace GamesEngineeringBase;

Tileset::Tileset() {}

int Tileset::getTileswide() const {
    return tileswide;
}

int Tileset::getTileshigh() const {
    return tileshigh;
}
void Tileset::load(string filename) {
    ifstream infile(filename);
    string s;
    string num;
    while (infile >> s) {
        if (s == "tileswide") {
            infile >> num;
            tileswide = stoi(num);
        }
        else if (s == "tileshigh") {
            infile >> num;
            tileshigh = stoi(num);
        }
        else if (s == "tilewidth") {
            infile >> num;
            tilewidth = stoi(num);
        }
        else if (s == "tileheight") {
            infile >> num;
            tileheight = stoi(num);
        }
        else if (s == "layer") {
            infile >> num;
            layer = stoi(num);
            break;
        }
    } //rewrite 

    arr2D = new int* [tileswide];
    for (int i = 0; i < tileshigh; i++) {
        arr2D[i] = new int[tileshigh];
    }

    for (int i = 0; i < tileswide; i++) {
        for (int j = 0; j < tileshigh; j++) {
            if (getline(infile, s, ',')) { //txt 横着存 数组是竖着存的 适用于tileswide==high
                arr2D[j][i] = stoi(s);
            }
        }
    }
}
const int Tileset::getTileIndex(int i, int j)const {
    if (i < 0 || i >= tileshigh || j < 0 || j >= tileswide) { //0<i j<41
        //std::cerr << "Index out of bounds: (" << i << ", " << j << ")" << std::endl;
        return -1; // 或者处理为其他合适的默认值
    }
    return arr2D[i][j];
}