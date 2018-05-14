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

#include <Zelta/Export.hpp>

#include <SFML/Graphics/RenderTexture.hpp>

namespace zt {
    class EXPORT Tileset {
    public:
        Tileset();
        virtual ~Tileset();

        const sf::Texture& getTextureForTile(unsigned int i) const;
        
        void create(sf::Texture& texture, const sf::Vector2u& size);
        void create(sf::Texture& texture, const sf::Vector2u& tiles, sf::Vector2f padding, sf::Vector2f margin);
        
    private:
        std::vector<sf::Texture> textures;

    };
}
#endif /* TILESET_HPP */

