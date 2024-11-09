#include "GameObject.h"
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
    int startPosX = screenPos.x;
    int startPosY = screenPos.y - 8;
    for (unsigned int i = 0; i < maxHealth; i++) {
        for (unsigned int j = 0; j < barHeight; j++) {
            if (startPosX + i >= 0 && startPosX + i < canvas.getWidth() &&
                startPosY + j >= 0 && startPosY + j < canvas.getHeight()) {
                canvas.draw(i + startPosX, j + startPosY, 0, 0, 0);
                if (i <= health) canvas.draw(i + startPosX, j + startPosY, 255, 0, 0);
            }
        }
    }
}

void GameObject::updateProjectiles(float dt, GameObject& obj, Camera& camera) {
    //launch projectiles from the middle position of NPC sprite
    Vec2 midWorldPos;
    midWorldPos.x = worldPos.x + sprite.width / 2;
    midWorldPos.y = worldPos.y + sprite.height / 2;
    Vec2 midObjWorldPos;
    midObjWorldPos.x = obj.getWorldPos().x + obj.getSpriteSize() / 2;
    midObjWorldPos.y = obj.getWorldPos().y + obj.getSpriteSize() / 2;
    projs.update(dt, midWorldPos, midObjWorldPos, camera);
    if (projs.checkProjEntityCollision(midObjWorldPos, obj.getSpriteSize())) {
        obj.setIfStartFlicker(true);
    }
}

void GameObject::drawProjectiles(Window& canvas, int projSize, Vec3 color) {
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