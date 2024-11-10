#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Utils.h"   
#include "GamesEngineeringBase.h"
#include "Camera.h"
#include "ProjsManager.h"

class GameObject { //inherited by Player and NPC class
protected:
	Vec2 worldPos; // object's (x,y) position in world coordinate system
	Vec2 screenPos; // object's (x,y) position in screen coordinate system
	GamesEngineeringBase::Image sprite; // object's sprite

	ProjsManager projs; // object's projectiles manager
	float ProjSpeed; // the speed of object's projectiles
	int shootingRange; // Maximum distance the object's projectiles can travel

	int health=1000; // Initial health level of the object; decreases when the object is attacked
	int maxHealth=1000; // Initial health level of the object, won't decrease
	float speed=0.f;

	bool ifStartFlicker = false; // Indicates if object should start flickering (e.g., upon being hit)
	float flickerDuration = 0.2f; // total duration for flicker effect
	float flickerTimer = 0.0f; // track current elapsed time for flicker effect
public:
	Vec2 getWorldPos() const {
		return worldPos;
	}
	int getSpriteSize() const {
		return sprite.width;
	}
	void setIfStartFlicker(bool flag) { //set the flag to start or stop flicker effect
		ifStartFlicker = flag;
	}
	// update function--------------------------------------------------------
	virtual void updateProjectiles(float dt, GameObject& obj, Camera& camera);
	void updateFlickerState(float dt);
	// draw function--------------------------------------------------------
	// draw gameobject: player/NPC
	void draw(GamesEngineeringBase::Window& canvas); 
	// player/NPC flicker when it is hit or collided with other entity
	void drawFlicker(GamesEngineeringBase::Window& canvas, Vec3 flickerColor); 
	// draw health bar of NPC
	void drawHealthBar(GamesEngineeringBase::Window& canvas); 
	// draw projectiles launched by player / NPC
	void drawProjectiles(GamesEngineeringBase::Window& canvas, int ProjSize, Vec3 color); 

	bool getIsAlive(); // used for check if NPC is alive (health <= 0)
	void applyDamage(int value); // health level decrease with specific value
};

#endif
