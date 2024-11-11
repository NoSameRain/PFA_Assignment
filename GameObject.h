#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Utils.h"   
#include "GamesEngineeringBase.h"
#include "Camera.h"
#include "ProjsManager.h"

using namespace std;

class GameObject { //inherited by Player and NPC class
protected:
	Vec2 worldPos; // object's (x,y) position in world coordinate system
	Vec2 screenPos; // object's (x,y) position in screen coordinate system
	GamesEngineeringBase::Image sprite; // object's sprite
	string Spritefilename;

	ProjsManager projs; // object's projectiles manager
	float ProjSpeed; // the speed of object's projectiles
	int shootingRange; // Maximum distance the object's projectiles can travel

	int health=500; // Initial health level of the object; decreases when the object is attacked
	int maxHealth=500; // Initial health level of the object, won't decrease
	float speed=0.f;

	// Indicates if object should start flickering (e.g., upon being hit)
	// ifStartFlicker == 0 : don't flicker
	// ifStartFlicker == 1 : flicker the color which NPC/Player has defined
	// ifStartFlicker == 2 : flicker green color to show AOE attack works
	unsigned int ifStartFlicker = 0; 

	float flickerDuration = 0.2f; // total duration for flicker effect
	float flickerTimer = 0.0f; // track current elapsed time for flicker effect
public:
	GameObject& operator=(const GameObject& other);
	Vec2 getWorldPos() const {
		return worldPos;
	}
	int getSpriteSize() const {
		return sprite.width;
	}
	void setIfStartFlicker(int flag) { //set the flag to start or stop flicker effect
		ifStartFlicker = flag;
	}
	string getSpriteName() {
		return Spritefilename;
	}
	int getMaxHealth() const{
		return maxHealth;
	}
	void setSprite() {
		sprite.load(Spritefilename);
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

	//serialization------------------------------------
	virtual void serialize(ofstream& out) const;
	virtual void deserialize(ifstream& in);
};

#endif
