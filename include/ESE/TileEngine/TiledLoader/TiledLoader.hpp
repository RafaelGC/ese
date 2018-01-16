/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TiledLoader.hpp
 * Author: rafa
 *
 * Created on January 14, 2018, 8:33 PM
 */

#ifndef ESE_TILEDLOADER_HPP
#define ESE_TILEDLOADER_HPP

#include <ESE/TileEngine/TiledLoader/Map.hpp>
#include <ESE/TileEngine/TiledLoader/Layer.hpp>
#include <SFML/System/Vector2.hpp>

namespace ESE {
    namespace Tiled {
        class TiledLoader {
        public:
            TiledLoader();
            virtual ~TiledLoader();

            Map loadFromFile(const std::string& file);
            
            virtual void sizeLoaded(sf::Vector2u mapSize, const sf::Vector2u& tileSize) {};
            virtual void layerLoaded(Layer layer) {};
            virtual void objectLayerLoaded(ObjectLayer objectGroup) {};
            
        private:
        };
    }
}

#endif /* TILEDLOADER_HPP */

