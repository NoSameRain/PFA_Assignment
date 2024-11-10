#include "ProjsManager.h"
#include <iostream>
using namespace std;
using namespace GamesEngineeringBase;

ProjsManager::ProjsManager(){}

ProjsManager::~ProjsManager() {
    for (int i = 0; i < currentSize; i++) {
        delete projs[i];
    }
}

void ProjsManager::generateProjs(float dt, Vec2 worldPos, Vec2 target, float speed, int shootingRange) {
    timeElapsed += dt;
    if (currentSize < maxProjSize) {
        if (timeElapsed > timeThreshold) {
            Projectile* proj = new Projectile(worldPos, target, speed, shootingRange);
            projs[currentSize++] = proj;
            timeElapsed = 0.f;
            //cout << "player" << worldPos.x << " " << worldPos.y << endl;
        }
    }
}

// delete the projectile which's isAlive == false
void ProjsManager::checkDeleteProj(unsigned int i) {
    if (!projs[i]->getIsAlive()) { //dead
        Projectile* _p = projs[i];
        projs[i] = nullptr;
        delete _p;
        //cout << "delete projctile: " << i << endl;
    }
}

void ProjsManager::update(float dt, Vec2 worldPos, Vec2 objWorldPos, Camera& camera, float speed, int shootingRange) {
    generateProjs(dt, worldPos, objWorldPos, speed, shootingRange);
    
    for (int i = 0; i < currentSize; i++) {
        if (projs[i] != nullptr) { 
            // update projectile movement
            projs[i]->update(dt, camera);
            // if projectile move out of shooting range, set isAlive as false
            // and delete this projectile
            checkDeleteProj(i);
        }
    }
}

// check if any projectile hit the target (Player/NPC)
bool ProjsManager::checkProjEntityCollision(Vec2 objWorldPos, int sprietSize) {
    for (int i = 0; i < currentSize; i++) {
        if (projs[i] != nullptr) {
            if (projs[i]->checkCollision(objWorldPos, sprietSize)) {
                // if projectile hit the target, set isAlive as false
                // and delete this projectile
                checkDeleteProj(i);
                return true;
            }
        }
    }
    return false;
}

void ProjsManager::draw(Window& canvas, int projSize, Vec3 color) {
    for (int i = 0; i < currentSize; i++) {
        if (projs[i] != nullptr) {
            projs[i]->draw(canvas, projSize, color);
        }
    }
}