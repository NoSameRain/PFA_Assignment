#include "GameObject.h"
#include <iostream>
#include <fstream>
using namespace GamesEngineeringBase;

GameObject& GameObject::operator=(const GameObject& other) {
    if (this == &other) {
        return *this; // Handle self-assignment
    }

    // Copy simple data members
    worldPos.x = other.worldPos.x;
    worldPos.y = other.worldPos.y;
    screenPos.x = other.screenPos.x;
    screenPos.y = other.screenPos.y;
    health = other.health;
    speed = other.speed;
    ifStartFlicker = other.ifStartFlicker;
    sprite.load(Spritefilename);

    return *this;
}

void GameObject::draw(Window& canvas) {
    for (unsigned int i = 0; i < sprite.width; i++) {
        for (unsigned int j = 0; j < sprite.height; j++) {
            if (screenPos.x + i >= 0 && screenPos.x + i < canvas.getWidth() &&
                screenPos.y + j >= 0 && screenPos.y + j < canvas.getHeight()) {
                if (sprite.alphaAt(i, j) > 200) {
                    canvas.draw(i + screenPos.x, j + screenPos.y, sprite.at(i, j));
                }
            }
        }
    }
}
void GameObject::drawFlicker(Window& canvas, Vec3 flickerColor) {
    if (ifStartFlicker != 0) {
        for (unsigned int i = 0; i < sprite.width; i++) {
            for (unsigned int j = 0; j < sprite.height; j++) {
                if (screenPos.x + i >= 0 && screenPos.x + i < canvas.getWidth() &&
                    screenPos.y + j >= 0 && screenPos.y + j < canvas.getHeight()) {
                    if (sprite.alphaAt(i, j) > 200) {
                        if(ifStartFlicker == 1) canvas.draw(i + screenPos.x, j + screenPos.y, flickerColor.x, flickerColor.y, flickerColor.z);
                        else canvas.draw(i + screenPos.x, j + screenPos.y, 0, 255, 70); 
                    }
                }
            }
        }
    } 
}

void GameObject::drawHealthBar(Window& canvas) {
    int barHeight = 4;
    //draw health bar start from NPC's screen system position and higher than the top of NPC's sprite
    int startPosX = screenPos.x;
    int startPosY = screenPos.y - 8;
    // maxHealth will be drawn as a black background bar, represents initial health value
    // health will decrease as NPC is attacked, so the red health bar will become shorter
    for (unsigned int i = 0; i < maxHealth/10; i++) {
        for (unsigned int j = 0; j < barHeight; j++) {
            if (startPosX + i >= 0 && startPosX + i < canvas.getWidth() &&
                startPosY + j >= 0 && startPosY + j < canvas.getHeight()) {
                //draw black maxHealth bar as background
                canvas.draw(i + startPosX, j + startPosY, 0, 0, 0);
                //draw red health bar based on the current health level
                if (i <= health/10) canvas.draw(i + startPosX, j + startPosY, 255, 0, 0);
            }
        }
    }
}

void GameObject::updateProjectiles(float dt, GameObject& obj, Camera& camera) {
    // midWorldPos: the starting position of projectiles,
    // -- calculated as the center of the NPC/Player sprite
    Vec2 midWorldPos;
    midWorldPos.x = worldPos.x + sprite.width / 2;
    midWorldPos.y = worldPos.y + sprite.height / 2;

    // midObjWorldPos: the target position for projectiles, 
    // -- calculated as the center of the target (Player/NPC) sprite
    Vec2 midObjWorldPos;
    midObjWorldPos.x = obj.getWorldPos().x + obj.getSpriteSize() / 2;
    midObjWorldPos.y = obj.getWorldPos().y + obj.getSpriteSize() / 2;

    // update projectiles' state
    projs.update(dt, midWorldPos, midObjWorldPos, camera, ProjSpeed, shootingRange);

    // check if projectiles hit the target (Player/NPC)
    if (projs.checkProjEntityCollision(midObjWorldPos, obj.getSpriteSize())) {
        // set flag to draw target with flickering effect to show it's hitted by projectile
        obj.setIfStartFlicker(1);
        // reduce target obj health value for 60 when hit by each projectile
        obj.applyDamage(linearDamage);
    }
}

void GameObject::drawProjectiles(Window& canvas, int projSize, Vec3 color) {
    //draw each projectile with specific width/height and color
    projs.draw(canvas, projSize, color);
}

void GameObject::updateFlickerState(float dt) {
    // checks if the flicker effect should stop based on elapsed time 
    if (ifStartFlicker!=0) {
        if (flickerTimer < flickerDuration) flickerTimer += dt;
        else {
            ifStartFlicker = 0;
            flickerTimer = 0.f;
        }
    }
}

void GameObject::applyDamage(int value) {
    if (health > 0) health -= value;
    else health = 0;
}

bool GameObject::getIsAlive() {
    return(health > 0);
}

//serialization-----------------------------------
void GameObject::serialize(ofstream& out) const {
    out.write(reinterpret_cast<const char*>(&worldPos), sizeof(worldPos));
    out.write(reinterpret_cast<const char*>(&screenPos), sizeof(screenPos));
    //out.write(reinterpret_cast<const char*>(&Spritefilename), sizeof(Spritefilename));
    out.write(reinterpret_cast<const char*>(&ProjSpeed), sizeof(ProjSpeed));
    out.write(reinterpret_cast<const char*>(&shootingRange), sizeof(shootingRange));
    out.write(reinterpret_cast<const char*>(&health), sizeof(health));
    out.write(reinterpret_cast<const char*>(&maxHealth), sizeof(maxHealth));
    out.write(reinterpret_cast<const char*>(&speed), sizeof(speed));
    out.write(reinterpret_cast<const char*>(&ifStartFlicker), sizeof(ifStartFlicker));
    out.write(reinterpret_cast<const char*>(&flickerDuration), sizeof(flickerDuration));
    out.write(reinterpret_cast<const char*>(&flickerTimer), sizeof(flickerTimer));

    // serialize std::string
    size_t length = Spritefilename.size();
    out.write(reinterpret_cast<const char*>(&length), sizeof(length));
    out.write(Spritefilename.data(), length);
   // ProjsManager projs; ------------------------------
}

void GameObject::deserialize(ifstream& in) {
    in.read(reinterpret_cast<char*>(&worldPos), sizeof(worldPos));
    in.read(reinterpret_cast<char*>(&screenPos), sizeof(screenPos));
    //in.read(reinterpret_cast<char*>(&Spritefilename), sizeof(Spritefilename));
    in.read(reinterpret_cast<char*>(&ProjSpeed), sizeof(ProjSpeed));
    in.read(reinterpret_cast<char*>(&shootingRange), sizeof(shootingRange));
    in.read(reinterpret_cast<char*>(&health), sizeof(health));
    in.read(reinterpret_cast<char*>(&maxHealth), sizeof(maxHealth));
    in.read(reinterpret_cast<char*>(&speed), sizeof(speed));
    in.read(reinterpret_cast<char*>(&ifStartFlicker), sizeof(ifStartFlicker));
    in.read(reinterpret_cast<char*>(&flickerDuration), sizeof(flickerDuration));
    in.read(reinterpret_cast<char*>(&flickerTimer), sizeof(flickerTimer));

    // deserialize std::string
    size_t length;
    in.read(reinterpret_cast<char*>(&length), sizeof(length));
    Spritefilename.resize(length);
    in.read(&Spritefilename[0], length);
}