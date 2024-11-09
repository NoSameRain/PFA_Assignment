#include "NPC.h"
#include "Constants.h"
#include "math.h"
#include <iostream>
using namespace std;
using namespace GamesEngineeringBase;

NPC::NPC(Vec2 _pos, string filename, int _maxHealth, float _speed) {
    sprite.load(filename);
    worldPos.x = _pos.x;
    worldPos.y = _pos.y;
    maxHealth = _maxHealth;
    health = _maxHealth;
    speed = _speed;
}

int NPC::getNPCPlayerDistance() const {
    return NPCPlayerDistance;
}

int NPC::getSpeed() const {
    return speed;
}

void NPC::takeDamage() {
    health -= 3;
}

bool NPC::isAlive() {
    return(health > 0);
}

void NPC::update(float dt, Vec2& playerPos, Camera& cam) {
    int move = static_cast<int>(speed * dt);
    NPCPlayerDistance = static_cast<int>(sqrt(pow(worldPos.x - playerPos.x, 2) + pow(worldPos.y - playerPos.y, 2)));
    if (NPCPlayerDistance == 0) NPCPlayerDistance = 1;

    float moveX = move * (playerPos.x - worldPos.x) / NPCPlayerDistance;
    float moveY = move * (playerPos.y - worldPos.y) / NPCPlayerDistance;

    // check boundary
    int newPosX = worldPos.x + static_cast<int>(moveX);
    int newPosY = worldPos.y + static_cast<int>(moveY);
    bool c = (newPosX > 0 && newPosX + npcSpriteSize < mapWidth) && (newPosY > 0 && newPosY + npcSpriteSize < mapHeight);

    if (NPCPlayerDistance < aggroRange) isAggroActive = true;
    else isAggroActive = false;

    // when player enters the area below, NPC starts to move towards player / shoot 
    // when distance less than stopAggroDistance, npc won't move, so player can escape from npc
    if (c && NPCPlayerDistance > stopAggroDistance && NPCPlayerDistance < aggroRange) {
        worldPos.x = newPosX;
        worldPos.y = newPosY;
    }
    screenPos = cam.worldToScreen(worldPos); //might < 0

    // checks if the flicker effect should stop based on elapsed time 
    updateFlickerState(dt);
}

bool NPC::checkCollision(Vec2 playerPos) {
    int x2 = (worldPos.x - playerPos.x) * (worldPos.x - playerPos.x);
    int y2 = (worldPos.y - playerPos.y) * (worldPos.y - playerPos.y);
    float r = sqrtf(x2 + y2);
    float n = static_cast<float>(2 * npcSpriteSize / 3);
    return(r < n);
}

bool NPC::getIsAggroActive() {
    return isAggroActive;
}

