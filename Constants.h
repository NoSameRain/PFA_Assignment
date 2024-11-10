#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include"Utils.h"
extern const unsigned int mapWidth ;
extern const unsigned int mapHeight;

extern const unsigned int tileWidthHeight; //each tile png is 32*32 pixel

extern const unsigned int playerSpriteSize; //player png size is 48*48
extern const unsigned int npcSpriteSize;

extern const int aggroRange;
extern const int stopAggroDistance ;

extern const int linearAttackRange;
extern const int AOEAttackRange ;

extern const int linearDamage;
extern const int AOEDamage;

extern const float timeThreshold_cooldown;
extern float timeElapsed_cooldown;
extern bool ifStartCooldown;

extern const Vec3 NPCprojColor;
extern const Vec3 playerProjColor ;
extern const Vec3 playerFlickerColor;
extern const Vec3 NPCFlickerColor;

extern const int NPCprojWidth ;
extern const int playerProjWidth;

extern int scores;

#endif // CONSTANTS_H
