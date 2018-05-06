/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResourceNotFoundException.hpp
 * Author: rafa
 *
 * Created on February 20, 2018, 9:30 PM
 */

#ifndef ZELTALIB_RESOURCENOTFOUNDEXCEPTION_HPP
#define ZELTALIB_RESOURCENOTFOUNDEXCEPTION_HPP

#include <exception>

namespace zt {

    /**
     * @brief Exception throwed when a resource is not found.
     */
    class ResourceNotFoundException : public std::exception {
    public:
        ResourceNotFoundException() {}
        ResourceNotFoundException(const std::string& resourceName) : resourceName(resourceName) {}

        const char* what() const noexcept {
            return resourceName.c_str();
        }
    private:
        std::string resourceName;
    };
    
}

#endif /* RESOURCENOTFOUNDEXCEPTION_HPP */

