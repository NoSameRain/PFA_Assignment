#pragma once
#ifndef NPC_H
#define NPC_H

#include "Utils.h"   
#include "GamesEngineeringBase.h"
#include "Camera.h"
#include "GameObject.h"

class NPC : public GameObject {
private:
	int NPCPlayerDistance;
	bool isAggroActive = false;
public:
	NPC(Vec2 _pos,std::string filename,int _maxHealth,float _speed);
	int getNPCPlayerDistance() const;
	int getSpeed()const;
	bool isAlive();
	void update(float dt, Vec2& playerPos, Camera& cam);
	void takeDamage();
	bool checkCollision(Vec2 playerPos);

	bool getIsAggroActive();
};

#endif