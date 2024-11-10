#include "NPCmanager.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace GamesEngineeringBase;

NPCmanager::NPCmanager(){}

NPCmanager::~NPCmanager() {
    for (int i = 0; i < currentSize; i++) {
        delete npc_array[i];
    }
}

NPCmanager& NPCmanager::operator=(const NPCmanager& other) {
    if (this == &other) {
        return *this; // Handle self-assignment
    }
    
    // Copy simple data members
    currentSize = other.currentSize;
    timeElapsed = other.timeElapsed;

    // Delete existing NPCs in npc_array to prevent memory leaks
    for (int i = 0; i < maxNpcSize; ++i) {
        delete npc_array[i];
        npc_array[i] = nullptr;
    }

    // deep copy of the npc_array
    for (int i = 0; i < maxNpcSize; ++i) {
        if (other.npc_array[i] != nullptr) {
            npc_array[i] = new NPC(*other.npc_array[i]); // use NPC's copy constructor
            cout << "test " << endl;
        }
        else npc_array[i] = nullptr; // ensure null pointers are copied properly
    }

    // copy the sort_health_array 
    for (int i = 0; i < maxNpcSize; ++i) {
        sort_health_array[i] = other.sort_health_array[i];
    }

    return *this;
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
    // generate 4 types NPC with random start position, sprite, health and speed
    // generate in an increasing frequency
    timeElapsed += dt;
    if (currentSize < maxNpcSize) { // max NPC number is 40
        if (timeElapsed > timeThreshold) {
            Vec2 pos = generateStartPos(camera);
            // choose one type of NPC from 4 types randomly
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
            // add new NPC pointer to array
            NPC* _npc = new NPC(pos, filename,health,speed);
            npc_array[currentSize++] = _npc;
            timeElapsed = 0.f;
            // frequency of generation increases over time, as time threshold reduces
            timeThreshold -= 0.1f;
            //threshold keep reducing till it is 0.3f
            timeThreshold = max(0.3f, timeThreshold); 
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
    //generate random NPC outside camera view
    generateNPC(camera, dt);

    for (int i = 0; i < currentSize; i++) {
        sort_health_array[i].x = i;
        if (npc_array[i] != nullptr) {
            npc_array[i]->update(dt, playerPos, camera);
            // update NPC index and health in this array for sorting later
            sort_health_array[i].y = npc_array[i]->getHealth();
            // if NPC's alive state is false, delete it
            checkDeleteNPC(i);
        }
        else sort_health_array[i].y = 0;

    }
}

void NPCmanager::draw(Window& canvas) {
    for (int i = 0; i < currentSize; i++) {
        if (npc_array[i] != nullptr) {
            npc_array[i]->draw(canvas); // draw each NPC
            npc_array[i]->drawHealthBar(canvas); // draw each NPC's health bar
            npc_array[i]->drawFlicker(canvas, NPCFlickerColor); // draw each NPC's flicker effect
        }
    }
}

// if NPC collides with player, player will flicker as red color
// called in main game loop; if true, affect player flickering
// (more complex behaviors : if true, NPCs moving back)
void NPCmanager::checkNPCPlayerCollision(Player& player) {
    for (int i = 0; i < currentSize; i++) {
        if (npc_array[i] != nullptr) {
            if (npc_array[i]->checkCollision(player.getWorldPos())) {
                player.setIfStartFlicker(1);
            }
        }
    }
}

// generate & update projectiles for those NPC(shooter) whose speed is 0
void NPCmanager::setProjectiles(float dt, GameObject& obj, Camera& camera) {
    for (int i = 0; i < currentSize; i++) {
        if (npc_array[i] != nullptr && npc_array[i]->getSpeed() == 0.f && npc_array[i]->getIsAggroActive()) {
            npc_array[i]->updateProjectiles(dt, obj, camera);
        }
    }
}
// draw projectiles for those NPC(shooter) whose speed is 0
void NPCmanager::drawProjectiles(Window& canvas) {
    for (int i = 0; i < currentSize; i++) {
        if (npc_array[i] != nullptr && npc_array[i]->getSpeed() == 0.f && npc_array[i]->getIsAggroActive()) {
            npc_array[i]->drawProjectiles(canvas, NPCprojWidth, NPCprojColor);
        }
    }
}
// check if any NPC is in the linear attack range of player
bool NPCmanager::getIfNPCinPlayerAttackRange() {
    for (int i = 0; i < currentSize; i++) {
        if (npc_array[i] != nullptr && 
            npc_array[i]->getNPCPlayerDistance() < linearAttackRange) {
            return true;
        }
    }
    return false;
}

// return NPC pointer , which is closest to player, to trigger player's linear attack
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

void swap(Vec2& a, Vec2& b) {
    Vec2 tmp = a;
    a = b;
    b = tmp;
}

// QuickSortByHealth function: sorts an array of Vec2 structures based on 
// the 'y' value (representing health) in descending order.
// 
// arr: pointer to array of Vec2 structures to be sorted
// start: starting index of sorting
// end: ending index
void QuickSortByHealth(Vec2* arr, int start, int end)
{   
    // base case : if there's only one or none element in sub_array
    if (start >= end) return;
    int left = start;
    int right = end;
    int key = start; //set the pivot
    //partition array
    while (start < end)
    {
        // select the bigger one in the left
        // move [end] to left if [end]'s value less than pivot's
        while (arr[end].y <= arr[key].y && start < end) end--;
        // select the smaller one in the right
        // move [start] to right if [start]'s value bigger than pivot's
        while (arr[start].y >= arr[key].y && start < end) start++;
        // swap those out of order 
        swap(arr[start], arr[end]);
    }
    // place pivot
    swap(arr[key], arr[end]);
    key = end;
    // sort subarray
    QuickSortByHealth(arr, left, key - 1);
    QuickSortByHealth(arr, key + 1, right);
}


void NPCmanager::attackTopFiveHealthNPC() {
    // Vec2 sort_health_array[40]: each element is a Vec2{x,y} object
    // x: stores NPC* npc_array index
    // y: stores corresponding health value

    //sort sort_health_array in descending order based on 'y' value (health)
    QuickSortByHealth(sort_health_array, 0, 39);

    int cnt = 0;
    // for test: output all the sorted health value
    //cout << "health of all the NPCs generated currently: ";
    //for (int i = 0; i < currentSize; i++) cout << sort_health_array[i].y << " ";
    //cout << endl;
    //cout << "health of NPCs inside AOE range: ";
    for (int i = 0; i < currentSize; i++) {
        int index = sort_health_array[i].x;
        if (cnt < 5 && npc_array[index] != nullptr) {
            // for those NPCs whose health is highest, select at most 5 NPCs who is inside AOEAttackRange
            if (npc_array[index]->getNPCPlayerDistance() < AOEAttackRange) {
                // reduce NPC health level by AOEDamage value, which is less than linear attack Damage
                npc_array[index]->applyDamage(AOEDamage);
                // the NPC hit by AOE attack would flicker green to indicate damage taken
                npc_array[index]->setIfStartFlicker(2);
                cnt++;
                //cout << sort_health_array[i].y << " ";
            }
        }    
    }
    //cout << endl;
}
//serialization-----------------------------------------
void NPCmanager::serialize(ofstream& out) const {
    
    out.write(reinterpret_cast<const char*>(&currentSize), sizeof(currentSize));

    for (int i = 0; i < currentSize; i++) {
        bool hasNPC = (npc_array[i] != nullptr);
        out.write(reinterpret_cast<const char*>(&hasNPC), sizeof(hasNPC));
        if (hasNPC) {
            npc_array[i]->serialize(out);
            //cout << "write: " << npc_array[i]->getSpriteName() << endl;
            //std::cout << "npc write : " << npc_array[i]->getHealth() << std::endl;
        }
            
    }
    out.write(reinterpret_cast<const char*>(&timeElapsed), sizeof(timeElapsed));
    out.write(reinterpret_cast<const char*>(&sort_health_array), sizeof(sort_health_array));
    
}

void NPCmanager::deserialize(ifstream& in) {

    in.read(reinterpret_cast<char*>(&currentSize), sizeof(currentSize));

    for (int i = 0; i < currentSize; i++) {
        bool hasNPC;
        in.read(reinterpret_cast<char*>(&hasNPC), sizeof(hasNPC));
        if (hasNPC) {
            npc_array[i] = new NPC();
            npc_array[i]->deserialize(in);
            //cout << "read: "<<npc_array[i]->getSpriteName() << endl;
            npc_array[i]->setSprite();
            //std::cout << "npc read: " << npc_array[i]->getHealth() << std::endl;
        }
    }

    in.read(reinterpret_cast<char*>(&timeElapsed), sizeof(timeElapsed));
    in.read(reinterpret_cast<char*>(&sort_health_array), maxNpcSize * sizeof(Vec2));
}
