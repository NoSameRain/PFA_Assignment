#include "NPC.h"
#include "Constants.h"
#include "math.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace GamesEngineeringBase;

NPC::NPC(Vec2 _pos, string filename, int _maxHealth, float _speed) {
    Spritefilename = filename;
    sprite.load(Spritefilename);
    worldPos.x = _pos.x;
    worldPos.y = _pos.y;
    maxHealth = _maxHealth;
    health = _maxHealth;
    speed = _speed;
    ProjSpeed = 280.f; // speed of NPC's projectiles
    shootingRange = aggroRange + 80; // range of NPC launch projectiles 
}

NPC::NPC(const NPC& other) {
    NPCPlayerDistance = other.NPCPlayerDistance;
    isAggroActive = other.isAggroActive;
    sprite.load(Spritefilename); //
}

NPC& NPC::operator=(const NPC& other) {
    if (this == &other) {
        return *this; // Handle self-assignment
    }
    GameObject::operator=(other); // copy base class member
    NPCPlayerDistance = other.NPCPlayerDistance;
    isAggroActive = other.isAggroActive;
}

int NPC::getNPCPlayerDistance() const {
    return NPCPlayerDistance;
}

int NPC::getSpeed() const {
    return speed;
}

int NPC::getHealth() const {
    return health;
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

//serialization-----------------------------------------
void NPC::serialize(ofstream& out) const {
    // Call base class method
    GameObject::serialize(out);

    // specific method for Player
    out.write(reinterpret_cast<const char*>(&NPCPlayerDistance), sizeof(NPCPlayerDistance));
    out.write(reinterpret_cast<const char*>(&isAggroActive), sizeof(isAggroActive));

    // ProjsManager projs; ------------------------------
}

void NPC::deserialize(ifstream& in) {
    // Call base class method
    GameObject::deserialize(in);

    // specific method for Player
    in.read(reinterpret_cast<char*>(&NPCPlayerDistance), sizeof(NPCPlayerDistance));
    in.read(reinterpret_cast<char*>(&isAggroActive), sizeof(isAggroActive));
}

