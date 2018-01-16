#include <ESE/TileEngine/TileSprite.hpp>

namespace ESE {

    TileSprite::TileSprite() {
    }
    
    sf::Vector2f TileSprite::getSize() const {
        return sf::Vector2f(this->getGlobalBounds().width, this->getGlobalBounds().height);
    }
    
    void TileSprite::draw(sf::RenderTarget & target, sf::RenderStates states) const {
        target.draw((sf::Sprite)(*this), states);
        
    }
}