/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TiledFileNotFoundException.hpp
 * Author: rafa
 *
 * Created on January 15, 2018, 12:12 AM
 */

#ifndef ZELTALIB_TILED_FILENOTFOUNDEXCEPTION_HPP
#define ZELTALIB_TILED_FILENOTFOUNDEXCEPTION_HPP

#include <exception>


namespace zt {
    namespace Tiled {
        
        class FileNotFoundException : public std::exception {
            
        };
        
    }
}

#endif

