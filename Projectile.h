#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Utils.h"
#include "Camera.h"
#include "GamesEngineeringBase.h"
#include "Constants.h"

class Projectile{
private:
	Vec2 worldPos; // the projectile starts at the position of the entity(NPC/player) that fires it.
	Vec2 screenPos; // the postion used to render projectile in camera coordinates
	Vec2 targetPos; // set shooting target when projectile is generated, position is same as player/NPC who's gonna be hitted
	Vec2 stopPos; // if projectile doesn't hit the target, it will stop at  stopPosition
	float speed;
	int distanceProjMoved;
	int projTargetDistance;
	int shootingRange;

	bool isCollided = false; //if projectile hits the player/NPC
	bool isAlive = true; //when isAlive == false,delete the projectile
public:
	Projectile(Vec2 _worldPos, Vec2 _target, float _speed, int _shootingRange);
	~Projectile();
	void update(float dt, Camera& cam);
	void draw(GamesEngineeringBase::Window& canvas, int projSize, Vec3 color);
	bool checkCollision(Vec2 pos, int spriteSize); 
	bool getIsAlive();
	bool getIsCollided();
};

#endif