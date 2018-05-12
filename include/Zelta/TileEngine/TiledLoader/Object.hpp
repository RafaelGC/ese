/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Object.hpp
 * Author: rafa
 *
 * Created on January 16, 2018, 1:28 AM
 */

#ifndef ZELTALIB_TILED_OBJECT_HPP
#define ZELTALIB_TILED_OBJECT_HPP

#include <Zelta/Export.hpp>

#include <string>

namespace zt {
    namespace tiled {
        
        class EXPORT Object {
        public:
            Object(int id, const std::wstring& name, const std::wstring& type, int x, int y, int gid);
            Object(int id, const std::wstring& name, const std::wstring& type, int x, int y);
            
            int getId() const;
            const std::wstring& getName() const;
            const std::wstring& getType() const;
            int getX() const;
            int getY() const;
            int getGID() const;
            bool isTile() const;
            
        private:
            bool mIsTile;
            int x, y, gid, id;
            std::wstring name, type;
        };
        
    }
}

#endif /* OBJECT_HPP */

