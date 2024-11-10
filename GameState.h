#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <fstream>
#include "GamesEngineeringBase.h"
#include "Camera.h"
#include "Player.h"
#include "World.h"
#include "NPCmanager.h"
#include "NPC.h"
using namespace GamesEngineeringBase;
using namespace std;

class GameState {
private:
    string filename = "Resources/savegame.dat";
    Player& hero;
    Camera& camera;
    World& world;
    NPCmanager& npcs;
public:
    GameState(Player& _hero, Camera& _camera, World& _world, NPCmanager& _npcs) :
        hero(_hero), camera(_camera), world(_world), npcs(_npcs) {};
    void saveState();
    void loadState(Player& _hero, Camera& _camera, World& _world, NPCmanager& _npcs);
    Player& getPlayer() { return hero; }
    Camera& getCamera() { return camera; }
    World& getWorld() { return world; }
    NPCmanager& getNPCmanager() { return npcs; }
 };

#endif
