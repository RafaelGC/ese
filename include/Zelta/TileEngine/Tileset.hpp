/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tileset.hpp
 * Author: rafa
 *
 * Created on January 10, 2018, 11:39 PM
 */

#ifndef TILESET_HPP
#define TILESET_HPP

#include <SFML/Graphics/RenderTexture.hpp>

namespace zt {
    class Tileset {
    public:
        Tileset();
        virtual ~Tileset();

        /**
        * Devuelve el subrectángulo para un cierto tile. Los tiles se comienzan a contar
        * en 1.
        * @param i Identificador del tile.
        * @return Devuelve el subrectángulo de la textura que corresponde al tile pasado por parámetro.
        */
        const sf::Texture& getTextureForTile(unsigned int i) const;
        
        void create(sf::Texture& texture, const sf::Vector2u& size);
        
    private:
        std::vector<sf::Texture> textures;

    };
}
#endif /* TILESET_HPP */

