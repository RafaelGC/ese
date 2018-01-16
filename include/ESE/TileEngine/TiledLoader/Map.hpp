/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Map.hpp
 * Author: rafa
 *
 * Created on January 14, 2018, 11:35 PM
 */

#ifndef ESE_TILED_MAP_HPP
#define ESE_TILED_MAP_HPP

#include <ESE/TileEngine/TiledLoader/Layer.hpp>
#include <ESE/TileEngine/TiledLoader/ObjectLayer.hpp>

namespace ESE {
    namespace Tiled {
        
        class Map {
        public:
            enum Orientation { Orthogonal, Isometric, Staggered, Hexagonal };
            
            Map();
            Map(int width, int height, int tileWidth, int tileHeight, Orientation orientation);
            
            int getWidth() const;
            int getHeight() const;
            int getTileWidth() const;
            int getTileHeight() const;
            
            Orientation getOrientation() const;
            
            void addLayer(const Layer& layer);
            std::vector<Layer>& getLayers();
            
            void addObjectLayer(const ObjectLayer& objectLayer);
            std::vector<ObjectLayer>& getObjectLayers();
            
        protected:
            int width, height, tileWidth, tileHeight;
            Orientation orientation;
            std::vector<Layer> layers;
            std::vector<ObjectLayer> objectLayers;
        };
        
    }
}

#endif /* MAP_HPP */

