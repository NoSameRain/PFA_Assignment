#include "Projectiles.h"
#include<iostream>
using namespace GamesEngineeringBase;
using namespace std;

Projectiles::Projectiles(Vec2 _worldPos, Vec2 _target, float _speed, int _shootingRange) {
    worldPos = _worldPos;
	speed = _speed;
    targetPos = _target;
    distanceProjMoved = 0;
    shootingRange = _shootingRange;
    projTargetDistance = static_cast<int>(sqrt(pow(worldPos.x - targetPos.x, 2) + pow(worldPos.y - targetPos.y, 2)));
    // compute stopPosition by finding a point along the line between worldPos and targetPos, 
    // scaled to match a specified shootingRange
    stopPos.x = static_cast<int>(shootingRange * (targetPos.x - worldPos.x) / projTargetDistance) + worldPos.x;
    stopPos.y = static_cast<int>(shootingRange * (targetPos.y - worldPos.y) / projTargetDistance) + worldPos.y;
}

Projectiles::~Projectiles() {}

//when call this function, player/NPC has entered aggroRange
void Projectiles::update(float dt, Camera& cam) {
    int move = static_cast<int>(speed * dt);
    int distance = static_cast<int>(sqrt(pow(worldPos.x - stopPos.x, 2) + pow(worldPos.y - stopPos.y, 2)));
    
    if (distanceProjMoved < shootingRange) { //shootingRange is 550 
        float moveX = move * (stopPos.x - worldPos.x) / distance;
        float moveY = move * (stopPos.y - worldPos.y) / distance;

        worldPos.x += static_cast<int>(moveX);
        worldPos.y += static_cast<int>(moveY);
        screenPos = cam.worldToScreen(worldPos);
        distanceProjMoved += move;
    }
    else {
        isAlive = false;
    }
}

void Projectiles::draw(Window& canvas, int projSize, Vec3 color) {
    for(int i = 0; i < projSize; i++)
        for (int j = 0; j < projSize; j++) {
            if (screenPos.x + i >= 0 && screenPos.x + i < canvas.getWidth() &&
                screenPos.y + j >= 0 && screenPos.y + j < canvas.getHeight())
                    canvas.draw(i + screenPos.x, j + screenPos.y, color.x, color.y, color.z);
        }
}

bool Projectiles::checkCollision(Vec2 pos, int spriteSize) {
    int s = spriteSize / 2;
    // Check if the projectile's world position is within the bounds of the NPC's/Player's sprite area
    // If so, a collision is detected and the function returns true
    if (worldPos.x > pos.x - s && worldPos.x < pos.x + s - 6
        && worldPos.y > pos.y - s && worldPos.y < pos.y + s - 6) {
        isAlive = false;
        return true;
    }
    return false;
}

bool Projectiles::getIsAlive() {
    return isAlive;
}

bool Projectiles::getIsCollided() {
    return isCollided;
}