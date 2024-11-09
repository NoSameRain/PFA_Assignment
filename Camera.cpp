#include "Camera.h"
#include "Constants.h"
#include "Utils.h"  
#include "GamesEngineeringBase.h"

using namespace std;
using namespace GamesEngineeringBase;

Camera::Camera(Window& canvas) {
    width = canvas.getWidth();
    height = canvas.getHeight();
}
Vec2 Camera::getCameraPos() {
    return pos;
}
void Camera::update(const Vec2& playerPos) {
    //// 让摄像机位置跟随玩家位置，使玩家保持在画布中心
    pos.x = playerPos.x - getViewWidth()/2;
    pos.y = playerPos.y - getViewHeight() / 2;

    if (pos.x < 0)pos.x = 0;
    if (pos.y < 0)pos.y = 0;
    //use mapWidth not canvasWidth !!!
    if (pos.x + getViewWidth() > mapWidth)pos.x = mapWidth - getViewWidth();
    if (pos.y + getViewHeight() > mapHeight)pos.y = mapHeight - getViewHeight();
}
Vec2 Camera::worldToScreen(const Vec2& playerPos) const {
    Vec2 v;
    v.x = playerPos.x - pos.x;
    v.y = playerPos.y - pos.y;
    return v;
}