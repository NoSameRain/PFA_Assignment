#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Utils.h"  
#include "GamesEngineeringBase.h"

class Camera {
    Vec2 pos;
    int width;
    int height;
public:
    Camera(GamesEngineeringBase::Window& canvas);
    int getViewWidth() {
        return width;
    }
    int getViewHeight() {
        return height;
    }
    Vec2 getCameraPos();
    void update(const Vec2& playerPos);
    Vec2 worldToScreen(const Vec2& playerPos) const;
};

#endif