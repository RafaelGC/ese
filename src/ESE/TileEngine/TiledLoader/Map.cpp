/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <ESE/TileEngine/TiledLoader/Map.hpp>
#include <vector>

namespace ESE {
    namespace Tiled {
        Map::Map() : width(0), height(0), tileWidth(0), tileHeight(0), orientation(Orientation::Orthogonal) {
            
        }
        
        Map::Map(int width, int height, int tileWidth, int tileHeight, Orientation orientation) : 
            width(width), height(height), tileWidth(tileWidth), tileHeight(tileHeight), orientation(orientation) {
            
        }

        int Map::getWidth() const {
            return width;
        }
        
        int Map::getHeight() const {
            return height;
        }
        
        int Map::getTileWidth() const {
            return tileWidth;
        }
        
        int Map::getTileHeight() const {
            return tileHeight;
        }

        Map::Orientation Map::getOrientation() const {
            return orientation;
        }
        
        void Map::addLayer(const Layer& layer) {
            this->layers.push_back(layer);
        }
        
        std::vector<Layer>& Map::getLayers() {
            return layers;
        }
        
        void Map::addObjectLayer(const ObjectLayer& objectLayer) {
            this->objectLayers.push_back(objectLayer);
        }
        
        std::vector<ObjectLayer>& Map::getObjectLayers() {
            return objectLayers;
        }
    }
}