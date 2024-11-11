#include "Constants.h"

const unsigned int mapWidth = 1344;
const unsigned int mapHeight = 1344;

const unsigned int tileWidthHeight = 32; //each tile png is 32*32 pixel

const unsigned int playerSpriteSize = 48; //player png size is 48*48
const unsigned int npcSpriteSize = 32;

const int aggroRange = 450;
const int stopAggroDistance = 40;

const int linearAttackRange = 150;
const int AOEAttackRange = 300;

const int linearDamage = 90;
const int AOEDamage = 60;

const float timeThreshold_cooldown = 8.f;
float timeElapsed_cooldown = 0.f;
bool ifStartCooldown = false;

const Vec3 NPCprojColor = { 1,1,255 };
const Vec3 playerProjColor = { 1,255,1 };
const Vec3 playerFlickerColor = { 255,1,1 };
const Vec3 NPCFlickerColor = { 255,255,255 };

const int NPCprojWidth = 6;
const int playerProjWidth = 8;

int scores = 0;