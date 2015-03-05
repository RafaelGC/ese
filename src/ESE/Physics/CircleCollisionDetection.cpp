#include <ESE/Physics/CicleCollisionDetection.hpp>

bool CircleCollisionDetection::collision(float x1, float y2, float radius, float px, float py)
{
    float difX = abs(x1-px);
    float difY = abs(y2-py);
    return sqrt(difX*difX+difY*difY)<=radius;
}
