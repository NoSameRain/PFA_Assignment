#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Utils.h"   
#include "GamesEngineeringBase.h"
#include "Camera.h"
#include "ProjsManager.h"

class GameObject {
protected:
	Vec2 worldPos;
	Vec2 screenPos;
	GamesEngineeringBase::Image sprite;
	ProjsManager projs;
	int health=100;
	int maxHealth=100;
	float speed=0.f;
	bool ifStartFlicker = false;
	float flickerDuration = 0.2f; // total time for flicker 
	float flickerTimer = 0.0f; // current time for flicker
public:
	Vec2 getWorldPos() const {
		return worldPos;
	}
	int getSpriteSize() const {
		return sprite.width;
	}
	void setIfStartFlicker(bool flag) {
		ifStartFlicker = flag;
	}
	void draw(GamesEngineeringBase::Window& canvas);
	void drawFlicker(GamesEngineeringBase::Window& canvas, Vec3 flickerColor);
	void drawHealthBar(GamesEngineeringBase::Window& canvas);
	void updateProjectiles(float dt, GameObject& obj, Camera& camera);
	void drawProjectiles(GamesEngineeringBase::Window& canvas, int ProjSize, Vec3 color);
	void updateFlickerState(float dt);
};

#endif
