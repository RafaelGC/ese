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

#include <Zelta/TileEngine/Tileset.hpp>
#include <iostream>

namespace zt {
    Tileset::Tileset() {
    }
    

    Tileset::~Tileset() {
    }
    
    void Tileset::create(sf::Texture& texture, const sf::Vector2u& size) {
        sf::Image img = texture.copyToImage();
        
        for (int y = 0; y < texture.getSize().y / size.y; y++) {
            for (int x = 0; x < texture.getSize().x / size.x; x++) {
                sf::Texture texture;
                texture.loadFromImage(img, sf::IntRect(x * size.x, y * size.y, size.x, size.y));
                textures.push_back(texture);
            }
        }
    }
    
    void Tileset::create(sf::Texture& texture, const sf::Vector2u& tiles, sf::Vector2f padding = sf::Vector2f(), sf::Vector2f margin = sf::Vector2f()) {
        sf::Image img = texture.copyToImage();
        
        float currX = padding.x;
        float currY = padding.y;
        
        float sizeX = (texture.getSize().x - 2 * padding.x - (tiles.x - 1) * margin.x) / tiles.x;
        float sizeY = (texture.getSize().y - 2 * padding.y - (tiles.y - 1) * margin.y) / tiles.y;
        
        for (int y = 0; y < tiles.y; y++) {
            for (int x = 0; x < tiles.x; x++) {
                sf::Texture tx;
                tx.loadFromImage(img, sf::IntRect(currX, currY, sizeX, sizeY));

                textures.push_back(tx);

                currX += sizeX + margin.x;
            }
            
            currX = padding.x;
            currY += sizeY + margin.y;
        }
    }

    const sf::Texture& Tileset::getTextureForTile(unsigned int i) const {
        return textures[i - 1];
    }
    

}