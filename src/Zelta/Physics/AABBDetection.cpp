#include <Zelta/Physics/AABBDetection.hpp>
#include <stdexcept>

bool AABBDetection::collides(const sf::FloatRect& rect1, const sf::FloatRect& rect2) const
{
    return collides(rect1.left,rect1.top,rect1.width,rect1.height,
                    rect2.left,rect2.top,rect2.width,rect2.height);
}

bool AABBDetection::collides(float x1, float y1, float w1, float h1,
                             float x2, float y2, float w2, float h2) const
{
    if (x1+w1<x2) return false;
    if (x1>x2+w2) return false;
    if (y1+h1<y2) return false;
    if (y1>y2+h2) return false;
    return true;
}