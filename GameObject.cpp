#include "GameObject.h"
#include<iostream>
using namespace GamesEngineeringBase;

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
    if (ifStartFlicker) {
        for (unsigned int i = 0; i < sprite.width; i++) {
            for (unsigned int j = 0; j < sprite.height; j++) {
                if (screenPos.x + i >= 0 && screenPos.x + i < canvas.getWidth() &&
                    screenPos.y + j >= 0 && screenPos.y + j < canvas.getHeight()) {
                    if (sprite.alphaAt(i, j) > 200) {
                        canvas.draw(i + screenPos.x, j + screenPos.y, flickerColor.x, flickerColor.y, flickerColor.z);
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
        obj.setIfStartFlicker(true);
        // reduce target obj health value for 60 when hit by each projectile
        obj.applyDamage(60); 
    }
}

void GameObject::drawProjectiles(Window& canvas, int projSize, Vec3 color) {
    //draw each projectile with specific width/height and color
    projs.draw(canvas, projSize, color);
}

void GameObject::updateFlickerState(float dt) {
    // checks if the flicker effect should stop based on elapsed time 
    if (ifStartFlicker) {
        if (flickerTimer < flickerDuration) flickerTimer += dt;
        else {
            ifStartFlicker = false;
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