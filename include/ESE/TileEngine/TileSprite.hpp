#ifndef TILEDRAWABLE_HPP
#define TILEDRAWABLE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

namespace ESE {

    /**
     * @brief Es la representación gráfica de un tile. Su utilidad es la de ser dibujado en la
     * pantalla.
     * */
    class TileSprite : public sf::Sprite {
    private:

    public:
        TileSprite();
        
        virtual sf::Vector2f getSize() const;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };

}

#endif
