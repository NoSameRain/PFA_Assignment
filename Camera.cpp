#include "Camera.h"
#include "Constants.h"
#include "Utils.h"  
#include "GamesEngineeringBase.h"
#include <fstream>

using namespace std;
using namespace GamesEngineeringBase;

Camera::Camera(Window& canvas) {
    width = canvas.getWidth();
    height = canvas.getHeight();
}
Vec2 Camera::getCameraPos() {
    return position;
}
void Camera::update(const Vec2& playerPos) {
    // camera position should follow player position 
    // to make sure player is always in the center position of camera view
    position.x = playerPos.x - getViewWidth() / 2;
    position.y = playerPos.y - getViewHeight() / 2;

    // boundary check: keep camera view inside the map (1344*1344)
    // 
    // the left top corner of camera position should be bigger than (0,0)
    if (position.x < 0)position.x = 0;
    if (position.y < 0)position.y = 0;
    // and right bottom corner should be less than (1344,1344)
    if (position.x + getViewWidth() > mapWidth) position.x = mapWidth - getViewWidth();
    if (position.y + getViewHeight() > mapHeight) position.y = mapHeight - getViewHeight();
}
Vec2 Camera::worldToScreen(const Vec2& objPosition) const {
    // convert the object's position from world coordinate system to camera coordinate system
    // by subtracting the camera's position as an offset
    Vec2 v;
    v.x = objPosition.x - position.x;
    v.y = objPosition.y - position.y;
    return v;
}

//serialization-----------------------------------------
void Camera::serialize(ofstream& out) const {
    out.write(reinterpret_cast<const char*>(&position), sizeof(position));
}

void Camera::deserialize(ifstream& in) {
    in.read(reinterpret_cast<char*>(&position), sizeof(position));
}