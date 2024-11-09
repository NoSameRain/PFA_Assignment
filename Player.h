#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Utils.h"   
#include "World.h"
#include "GamesEngineeringBase.h"
#include "Camera.h"
#include "GameObject.h"

class Player : public GameObject {
private:
    float timeElapsed=0.f;
    float timeThreshold = 0.3f;
public:
    Player(int _x, int _y, std::string filename);
    void updateMovementAnim(std::string name);
    void update(float dt, GamesEngineeringBase::Window& canvas, World& world, Camera& cam);
};

#endif // PLAYER_H