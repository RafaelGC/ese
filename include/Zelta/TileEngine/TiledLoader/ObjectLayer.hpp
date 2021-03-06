/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ObjectLayer.hpp
 * Author: rafa
 *
 * Created on January 16, 2018, 1:40 AM
 */

#ifndef ZELTALIB_TILED_OBJECTLAYER_HPP
#define ZELTALIB_TILED_OBJECTLAYER_HPP

#include <vector>
#include <Zelta/TileEngine/TiledLoader/Object.hpp>

namespace zt {
    namespace tiled {
        
        class ObjectLayer {
        public:
            ObjectLayer(const std::wstring& name);
            
            void addObject(const Object& object);
            int size() const;
            Object& operator[](int index);
            const std::wstring& getName() const;
        private:
            std::vector<Object> objects;
            std::wstring name;
        };
        
    }
}

#endif /* OBJECTLAYER_HPP */

