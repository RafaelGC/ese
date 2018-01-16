/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tile.hpp
 * Author: rafa
 *
 * Created on January 14, 2018, 9:27 PM
 */

#ifndef ESE_TILED_TILE_HPP
#define ESE_TILED_TILE_HPP

namespace ESE {
    namespace Tiled {
        class Tile {
        public:
            Tile();
            Tile(int gid);
            
            int getGID() const;
        private:
            int gid;
            
        };
    }
}

#endif /* TILE_HPP */

