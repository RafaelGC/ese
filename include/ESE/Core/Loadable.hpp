/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Loadable.hpp
 * Author: rafa
 *
 * Created on January 18, 2018, 4:36 AM
 */

#ifndef ESE_LOADABLE_HPP
#define ESE_LOADABLE_HPP

#include <string>

namespace ESE {
    class Loadable {
    public:
        virtual void loadFromFile(const std::string & name, const std::string & path) = 0;
    };
}
#endif /* LOADABLE_HPP */

