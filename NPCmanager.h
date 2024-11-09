#pragma once
#ifndef NPCMANAGER_H
#define NPCMANAGER_H

#include "NPC.h"
#include "GameObject.h"
#include "GamesEngineeringBase.h"
#include "Player.h"
#include "Utils.h"

class NPCmanager{
    static const int maxNpcSize = 40;
    NPC* npc_array[maxNpcSize] = { nullptr };
    int currentSize = 0;
    float timeElapsed = 0.f;
    float timeThreshold = 3.f;
    void generateNPC(Camera& camera, float& dt);                                                             
    void checkDeleteNPC(unsigned int i);
    Vec2 generateStartPos(Camera& camera);
public:
    NPCmanager();
    ~NPCmanager();
    void update(float& dt, Vec2& playerPos, Camera& camera);
    void draw(GamesEngineeringBase::Window& canvas);
    void checkNPCPlayerCollision(Player& player);
    void setProjectiles(float dt, GameObject& obj, Camera& camera);
    void drawProjectiles(GamesEngineeringBase::Window& canvas);

    bool getIfNPCinPlayerAttackRange();
    NPC* const getClosestNPCtoPlayer();
};

#endif