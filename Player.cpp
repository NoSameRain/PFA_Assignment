#include "Player.h"
#include "World.h"
#include "Constants.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace GamesEngineeringBase;

Player::Player(int _x, int _y, string filename) {
    Spritefilename = filename;
    sprite.load(Spritefilename);
    worldPos.x = _x ;
    worldPos.y = _y ;
    speed = 220.f;
    ProjSpeed = 400.f; // speed of player's projectiles
    shootingRange = linearAttackRange; // range of player launch projectiles, as linear attack
}

Player& Player::operator=(const Player& other) {
    if (this == &other) {
        return *this; // Handle self-assignment
    }
    GameObject::operator=(other); // copy base class member
    timeElapsed_anim = other.timeElapsed_anim;
    ifApplyAOE = other.ifApplyAOE;
}

void Player::updateMovementAnim(string name) {
    string fileName1 = "Resources/" + name + "0.png";
    string fileName2 = "Resources/" + name + "1.png";
    if (timeElapsed_anim < timeThreshold_anim) sprite.load(fileName1);
    else if (timeElapsed_anim < 2 * timeThreshold_anim) {
        sprite.load(fileName2);
    }
    else timeElapsed_anim = 0.f;
}

void Player::update(float dt, Window& canvas, World& world, Camera& cam) {
    int move = static_cast<int>(speed * dt);
    int moveX = 0;
    int moveY = 0;

    timeElapsed_anim += dt;

    if (canvas.keyPressed('W')) {
        updateMovementAnim("up");
        moveY -= move;
    }
    if (canvas.keyPressed('S')) {
        updateMovementAnim("down");
        moveY += move;
    }
        
    if (canvas.keyPressed('A')) {
        updateMovementAnim("left");
        moveX -= move;
    }
        
    if (canvas.keyPressed('D')) {
        updateMovementAnim("right");
        moveX += move;
    }
    // apply AOE attack
    // only when it is not in cooldown time, press 'Q' can take effect
    if (canvas.keyPressed('Q') && !ifStartCooldown) {
        ifApplyAOE = true;
        //cout << "AOE applied" << endl;
    }

    int posXNew = worldPos.x + moveX;
    int posYNew = worldPos.y + moveY;

    if (world.checkTilePassable(posXNew, posYNew)) {
        worldPos.x = posXNew;
        worldPos.y = posYNew;
        if (worldPos.x < 0) worldPos.x = 0;
        if (worldPos.y < 0) worldPos.y = 0;
        if ((worldPos.x + playerSpriteSize) > mapWidth) worldPos.x = mapWidth - playerSpriteSize;
        if ((worldPos.y + playerSpriteSize) > mapHeight) worldPos.y = mapHeight - playerSpriteSize;
    }

    screenPos = cam.worldToScreen(worldPos);

    // checks if the flicker effect should stop based on elapsed time 
    updateFlickerState(dt);
}

//serialization-----------------------------------------
void Player::serialize(ofstream& out) const {
    // Call base class method
    GameObject::serialize(out); 

    // specific method for Player 
    out.write(reinterpret_cast<const char*>(&timeElapsed_anim), sizeof(timeElapsed_anim));
    out.write(reinterpret_cast<const char*>(&ifApplyAOE), sizeof(ifApplyAOE));

    // ProjsManager projs; ------------------------------
}

void Player::deserialize(ifstream& in) {
    // Call base class method
    GameObject::deserialize(in);

    // specific method for Player
    in.read(reinterpret_cast<char*>(&timeElapsed_anim), sizeof(timeElapsed_anim));
    in.read(reinterpret_cast<char*>(&ifApplyAOE), sizeof(ifApplyAOE));
}