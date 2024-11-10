#include "GameState.h"
#include "Constants.h"
#include <iostream>
//using namespace std;

void GameState::saveState() {
    ofstream outfile(filename, ios::binary);
    if (outfile.is_open()) {
        hero.serialize(outfile);
        camera.serialize(outfile);
        npcs.serialize(outfile);
        outfile.write(reinterpret_cast<const char*>(&timeElapsed_cooldown), sizeof(timeElapsed_cooldown));
        outfile.write(reinterpret_cast<const char*>(&ifStartCooldown), sizeof(ifStartCooldown));
        outfile.write(reinterpret_cast<const char*>(&scores), sizeof(scores));
        outfile.close();
        cout << "game saved succesfully!" << endl;
    }
    else {
        cerr << " can not open savegame file!" << endl;
    }
}

void GameState::loadState(Player& _hero, Camera& _camera, World& _world, NPCmanager& _npcs) {
    ifstream infile(filename, ios::binary);
    if (infile.is_open()) {
        hero.deserialize(infile);
        hero.setSprite();
        camera.deserialize(infile);
        npcs.deserialize(infile);
        infile.read(reinterpret_cast<char*>(&timeElapsed_cooldown), sizeof(timeElapsed_cooldown));
        infile.read(reinterpret_cast<char*>(&ifStartCooldown), sizeof(ifStartCooldown));
        infile.read(reinterpret_cast<char*>(&scores), sizeof(scores));
        infile.close();
        cout << "game loaded succesfully!" << endl;
        _hero = hero;
        _camera = camera;
        _npcs = npcs;
    }
    else {
        cerr << " can not open savegame file!" << endl;
    }
}
