#ifndef AABBDETECTION_HPP
#define AABBDETECTION_HPP

#include <SFML/Graphics/Rect.hpp>

class AABBDetection{
public:
    bool collides(const sf::FloatRect &rect1, const sf::FloatRect &rect2) const;
    bool collides(float x1, float y1, float w1, float h1,
                  float x2, float y2, float w2, float h2) const;
};

#endif