#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Utils.h"  
#include "GamesEngineeringBase.h"

class Camera {
private:   
    Vec2 position; // camera position in world corrdinate system
    int width; // camera view width
    int height; // camera view height
public:
    Camera(GamesEngineeringBase::Window& canvas);
    int getViewWidth() {
        return width;
    }
    int getViewHeight() {
        return height;
    }
    Vec2 getCameraPos(); // return camera position
    void update(const Vec2& playerPos); // update camera position based on player position
    Vec2 worldToScreen(const Vec2& objPosition) const; // convert the object's position from world system to camera system 
    //serialization------------------------------------
    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& in);
};

#endif