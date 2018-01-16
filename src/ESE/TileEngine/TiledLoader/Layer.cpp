/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <ESE/TileEngine/TiledLoader/Layer.hpp>

#include <vector>

namespace ESE {
    namespace Tiled {
        
        Layer::Layer() {
            this->width = this->height = 0;
        }
        
        Layer::Layer(const std::wstring& name, int width, int height) : 
            name(name), width(width), height(height) {
            
        }
        
        int Layer::getWidth() const {
            return width;
        }
        
        int Layer::getHeight() const {
            return height;
        }
        std::wstring Layer::getName() const {
            return name;
        }
        
        Tile& Layer::operator[](int index) {
            return this->tiles[index];
        }
        
        Tile& Layer::at(int x, int y) {
            return tiles[y * width + x];
        }
        
        void Layer::addTile(const Tile& tile) {
            this->tiles.push_back(tile);
        }
        
    }
}