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
	NPC(){}
	NPC(Vec2 _pos,std::string filename,int _maxHealth,float _speed);
	NPC(const NPC& other);
	NPC& operator=(const NPC& other);
	int getHealth() const;
	int getMaxHealth() const;
	int getNPCPlayerDistance() const;
	int getSpeed()const;
	void update(float dt, Vec2& playerPos, Camera& cam);
	bool checkCollision(Vec2 playerPos);
	bool getIsAggroActive();
	//serialization------------------------------------
	void serialize(std::ofstream& out) const;
	void deserialize(std::ifstream& in);
};

#endif