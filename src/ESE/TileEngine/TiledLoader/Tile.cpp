/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <ESE/TileEngine/TiledLoader/Tile.hpp>

namespace ESE {
    namespace Tiled {
        
        Tile::Tile() {
            this->gid = 0;
        }
        
        Tile::Tile(int gid) : gid(gid) {
        }
        
        int Tile::getGID() const {
            return gid;
        }
        
    }
}