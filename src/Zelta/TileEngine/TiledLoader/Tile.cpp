/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <Zelta/TileEngine/TiledLoader/Tile.hpp>

namespace zt {
    namespace tiled {
        
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