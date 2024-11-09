#pragma once
#ifndef PROJSMANAGER_H
#define PROJSMANAGER_H

#include "Projectiles.h"
#include "Utils.h"
#include "GamesEngineeringBase.h"

class ProjsManager {
private:
	static const int maxProjSize = 10000;
	Projectiles* projs[maxProjSize] = { nullptr };
	int currentSize = 0;
	float timeElapsed = 0.f;
	float timeThreshold = 0.8f;
public:
	ProjsManager();
	~ProjsManager();
	void generateProjs(float dt, Vec2 worldPos, Vec2 target);
	void checkDeleteProj(unsigned int i);
	void update( float dt, Vec2 worldPos, Vec2 objWorldPos, Camera& camera);
	bool checkProjEntityCollision(Vec2 objWorldPos, int sprietSize);
	void draw(GamesEngineeringBase::Window& canvas, int projSize, Vec3 color);

};

#endif