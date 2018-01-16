/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tileset.cpp
 * Author: rafa
 * 
 * Created on January 10, 2018, 11:39 PM
 */

#include <ESE/TileEngine/Tileset.hpp>

namespace ESE {
    Tileset::Tileset() {
    }
    

    Tileset::~Tileset() {
    }
    
    void Tileset::create(sf::Texture& texture, const sf::Vector2u& size) {
        sf::Image img = texture.copyToImage();
        
        for (int y = 0; y < texture.getSize().y / size.y; y++) {
            for (int x = 0; x < texture.getSize().x / size.x; x++) {
                sf::Texture texture;
                //texture.create(32, 32);
                
                texture.loadFromImage(img, sf::IntRect(x * size.x, y * size.y, size.x, size.y));
                textures.push_back(texture);
            }
        }
    }

    const sf::Texture& Tileset::getTextureForTile(unsigned int i) const {
        return textures[i - 1];
    }
    

}