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

void ProjsManager::generateProjs(float dt, Vec2 worldPos, Vec2 target) {
    timeElapsed += dt;
    if (currentSize < maxProjSize) {
        if (timeElapsed > timeThreshold) {
            Projectiles* proj = new Projectiles(worldPos, target, 300.f);
            projs[currentSize++] = proj;
            timeElapsed = 0.f;
            //cout << "player" << worldPos.x << " " << worldPos.y << endl;
        }
    }
}

void ProjsManager::checkDeleteProj(unsigned int i) {
    if (!projs[i]->getIsAlive()) { //dead
        Projectiles* _p = projs[i];
        projs[i] = nullptr;
        delete _p;
        //cout << "delete projctile: " << i << endl;
    }
}

void ProjsManager::update(float dt, Vec2 worldPos, Vec2 objWorldPos, Camera& camera) {
    generateProjs(dt, worldPos, objWorldPos);
    
    for (int i = 0; i < currentSize; i++) {
        if (projs[i] != nullptr) { 
            projs[i]->update(dt, camera);
            checkDeleteProj(i);
        }
    }
}

bool ProjsManager::checkProjEntityCollision(Vec2 objWorldPos, int sprietSize) {
    for (int i = 0; i < currentSize; i++) {
        if (projs[i] != nullptr) {
            if (projs[i]->checkCollision(objWorldPos, sprietSize)) {
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