/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <Zelta/TileEngine/TiledLoader/Object.hpp>

namespace zt {
    namespace Tiled {
        
        Object::Object(int id, const std::wstring& name, const std::wstring& type, int x, int y, int gid) :
            Object(id, name, type, x, y) {
            mIsTile = true;
        }
        
        Object::Object(int id, const std::wstring& name, const std::wstring& type, int x, int y) : 
            id(id), name(name), type(type), x(x), y(y) {
            mIsTile = false;
        }

        int Object::getId() const {
            return id;
        }
        
        const std::wstring& Object::getName() const {
            return name;
        }
        
        const std::wstring& Object::getType() const {
            return type;
        }
        
        int Object::getX() const {
            return x;
        }
        
        int Object::getY() const {
            return y;
        }
        
        int Object::getGID() const {
            return gid;
        }
        
        bool Object::isTile() const {
            return mIsTile;
        }
        
    }
}