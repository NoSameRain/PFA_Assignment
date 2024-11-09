#include "Player.h"
#include "World.h"
#include "Constants.h"
#include <iostream>

using namespace std;
using namespace GamesEngineeringBase;

Player::Player(int _x, int _y, string filename) {
    sprite.load(filename);
    worldPos.x = _x ;
    worldPos.y = _y ;
    speed = 220.f;
    ProjSpeed = 400.f; // speed of player's projectiles
    shootingRange = linearAttackRange; // range of player launch projectiles, as linear attack
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
    if (canvas.keyPressed('Q')) {
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

//void Player::applyAOE() {

//}

//bool Player::checkCollision(NPC& p) {
//    int x2 = (worldPos.x - p.worldPos.x) * (worldPos.x - p.worldPos.x);
//    int y2 = (worldPos.y - p.worldPos.y) * (worldPos.y - p.worldPos.y);
//    float r = sqrtf(x2 + y2);
//    float n = static_cast<float>(2 * playerSpriteSize / 3);
//    return(r < n);
//}