/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Argument.hpp
 * Author: rafa
 *
 * Created on January 22, 2018, 12:41 PM
 */

#ifndef ZELTALIB_ARGUMENT_HPP
#define ZELTALIB_ARGUMENT_HPP

#include <Zelta/Export.hpp>
#include <string>

namespace zt {

    /**
     * @brief Represents an argument.
     */
    class EXPORT Argument {
    public:
        Argument(const std::string& argument);
        const std::string& toString() const;
        int toInt() const;
        float toFloat() const;
        double toDouble() const;
    private:
        std::string arg;
    };
}
#endif

