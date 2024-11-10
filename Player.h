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
    float timeElapsed_anim = 0.f; // time elapsed for player movement animation
    float timeThreshold_anim = 0.3f; // time threshold for movement animation to update
    bool ifApplyAOE = false; // when press key 'Q', ifApplyAOE = true

public:
    Player(int _x, int _y, std::string filename);
    Player& operator=(const Player& other);
    bool getIfApplyAOE() {
        return ifApplyAOE;
    }
    void setAOE(bool flag) {
        ifApplyAOE = flag;
    }
    void updateMovementAnim(std::string name); //update player walking animation 
    void update(float dt, GamesEngineeringBase::Window& canvas, World& world, Camera& cam);

    //serialization------------------------------------
    void serialize(ofstream& out) const;
    void deserialize(ifstream& in);
};

#endif // PLAYER_H