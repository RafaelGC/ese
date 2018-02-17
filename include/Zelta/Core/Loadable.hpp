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

#ifndef ZELTALIB_LOADABLE_HPP
#define ZELTALIB_LOADABLE_HPP

#include <string>

/**
 * @brief Base class for things that can be loaded.
 */
namespace zt {
    class Loadable {
    public:
        virtual ~Loadable() {};
        virtual void loadFromFile(const std::string & name, const std::string & path) = 0;
        virtual void loadFromMemory(const std::string& name, const void* data, std::size_t size) = 0;
        virtual const std::string& getName() const = 0;
    };
}
#endif /* LOADABLE_HPP */

