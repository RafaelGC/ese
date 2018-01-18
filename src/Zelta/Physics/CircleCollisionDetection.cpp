#include <Zelta/Physics/CicleCollisionDetection.hpp>
#include <cmath>

bool CircleCollisionDetection::collision(float x1, float y2, float radius, float px, float py)
{
    float difX = std::abs(x1-px);
    float difY = std::abs(y2-py);
    return sqrt(difX*difX+difY*difY)<=radius;
}
