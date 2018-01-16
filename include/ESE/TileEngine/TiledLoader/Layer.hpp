/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Layer.hpp
 * Author: rafa
 *
 * Created on January 14, 2018, 10:34 PM
 */

#ifndef ESE_TILED_LAYER_HPP
#define ESE_TILED_LAYER_HPP

#include <string>
#include <vector>

#include <ESE/TileEngine/TiledLoader/Tile.hpp>

namespace ESE {
    namespace Tiled {
        
        class Layer {
        public:
            Layer();
            Layer(const std::wstring& name, int width, int height);
            
            int getWidth() const;
            int getHeight() const;
            std::wstring getName() const;
            
            Tile& operator[](int index);
            Tile& at(int x, int y);
            
            void addTile(const Tile& tile);
            
        protected:
            std::vector<Tile> tiles;
            std::wstring name;
            int width, height;
        };
        
    }
}

#endif /* LAYER_HPP */

