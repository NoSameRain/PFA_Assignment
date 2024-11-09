#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include"Utils.h"
const unsigned int mapWidth = 1344;
const unsigned int mapHeight = 1344;

const unsigned int tileWidthHeight = 32; //each tile png is 32*32 pixel

const unsigned int playerSpriteSize = 48; //player png size is 48*48
const unsigned int npcSpriteSize = 32;

const unsigned int tileType = 26; //26 diff tile
const int aggroRange = 500;
const int stopAggroDistance = 72;

const Vec3 NPCprojColor = { 1,1,255 };
const Vec3 playerProjColor = { 1,255,1 };
const Vec3 playerFlickerColor = { 255,1,1 };
const Vec3 NPCFlickerColor = { 255,255,255 };

const int NPCprojWidth = 6;
const int playerProjWidth = 10;

#endif // CONSTANTS_H
