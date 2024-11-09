#include "NPCmanager.h"
#include <iostream>
using namespace std;
using namespace GamesEngineeringBase;

NPCmanager::NPCmanager(){}

NPCmanager::~NPCmanager() {
    for (int i = 0; i < currentSize; i++) {
        delete npc_array[i];
    }
}

//it might be quick when map size super larger than camera view
Vec2 NPCmanager::generateStartPos(Camera& camera) {
    Vec2 camPos = camera.getCameraPos();
    int camPosX = camPos.x;
    int camPosY = camPos.y;
    int width = camera.getViewWidth();
    int height = camera.getViewHeight();
    bool t1, t2, flag=true;
    int x, y;
    //keep generating random position until find a position outside the camera view
    do {
        x = rand() % mapWidth;
        y = rand() % mapHeight;
        //inside map
        t1 = (x > 0 && x + npcSpriteSize < mapWidth) && (y>0 && y + npcSpriteSize < mapHeight);
        //inside camera view
        t2 = (x + npcSpriteSize >= camPosX && x <= camPosX + width) && (y + npcSpriteSize >= camPosY && y <= camPosY + height);
        //if inside map and outside the camera view, break
        if (t1 == true && t2 == false) {
            flag = false;
        }
    //if inside map and outside camera view then break
    } while (flag);

    Vec2 t;
    t.x = x;
    t.y = y;

    return t;
}

void NPCmanager::generateNPC(Camera& camera, float& dt) {
    timeElapsed += dt;
    if (currentSize < maxNpcSize) {
        if (timeElapsed > timeThreshold) {
            Vec2 pos = generateStartPos(camera);
            int NPCtypeIndex = rand() % 4;
            int health = 0;
            float speed = 0.f;
            string filename = "Resources/npc" + to_string(NPCtypeIndex) + ".png";
            switch (NPCtypeIndex) {
            case 0:
                health = 360;
                speed = 0.f; //shooter
                break;
            case 1:
                health = 180;
                speed = 430.f;
                break;
            case 2:
                health = 240;
                speed = 300.f;
                break;
            case 3:
                health = 300;
                speed = 250.f;
                break;
            }

            NPC* _npc = new NPC(pos, filename,health,speed);
            //cout << "Created: " << currentSize << '\t' << timeThreshold << '\t' << dt << endl;

            npc_array[currentSize++] = _npc;
            timeElapsed = 0.f;
            timeThreshold -= 0.1f;
            timeThreshold = max(0.3f, timeThreshold); //threshold keep reducing till it is 0.2f 
        }
    }
}
void NPCmanager::checkDeleteNPC(unsigned int i) {
    if (!npc_array[i]->getIsAlive()) { //dead
        NPC* _npc = npc_array[i];
        npc_array[i] = nullptr;
        delete _npc;
        cout << "kILLED NPC: " << i << endl;
    }
}

void NPCmanager::update(float& dt, Vec2& playerPos, Camera& camera) {
    generateNPC(camera, dt);
    for (int i = 0; i < currentSize; i++) {
        if (npc_array[i] != nullptr) {
            npc_array[i]->update(dt, playerPos, camera);
            checkDeleteNPC(i);
        }
    }
}

void NPCmanager::draw(Window& canvas) {
    for (int i = 0; i < currentSize; i++) {
        if (npc_array[i] != nullptr) {
            npc_array[i]->draw(canvas);
            npc_array[i]->drawHealthBar(canvas);
            npc_array[i]->drawFlicker(canvas, NPCFlickerColor);
        }
    }
}

// called in main game loop; if true, affect player flickering
// (more complex behaviors : if true, NPCs moving back)
void NPCmanager::checkNPCPlayerCollision(Player& player) {
    for (int i = 0; i < currentSize; i++) {
        if (npc_array[i] != nullptr) {
            if (npc_array[i]->checkCollision(player.getWorldPos())) {
                player.setIfStartFlicker(true);
            }
        }
    }
}

void NPCmanager::setProjectiles(float dt, GameObject& obj, Camera& camera) {
    for (int i = 0; i < currentSize; i++) {
        if (npc_array[i] != nullptr && npc_array[i]->getSpeed() == 0.f && npc_array[i]->getIsAggroActive()) {
            npc_array[i]->updateProjectiles(dt, obj, camera);
        }
    }
}

void NPCmanager::drawProjectiles(Window& canvas) {
    for (int i = 0; i < currentSize; i++) {
        if (npc_array[i] != nullptr && npc_array[i]->getSpeed() == 0.f && npc_array[i]->getIsAggroActive()) {
            npc_array[i]->drawProjectiles(canvas, NPCprojWidth, NPCprojColor);
        }
    }
}

bool NPCmanager::getIfNPCinPlayerAttackRange() {
    for (int i = 0; i < currentSize; i++) {
        if (npc_array[i] != nullptr && 
            npc_array[i]->getNPCPlayerDistance() < linearAttackRange) {
            return true;
        }
    }
    return false;
}

NPC* const NPCmanager::getClosestNPCtoPlayer() {
    int min = 1000;
    int index = -1;
    for (int i = 0; i < currentSize; i++) {
        if (npc_array[i] != nullptr && npc_array[i]->getIsAggroActive()) {
            if (min > npc_array[i]->getNPCPlayerDistance()) {
                min = npc_array[i]->getNPCPlayerDistance();
                index = i;
            }
        }
    }
    if (index == -1) {
        //cout << " no closest NPC to player" << endl;
        return nullptr;
    }
    return npc_array[index];
}
