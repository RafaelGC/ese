/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Text.hpp
 * Author: rafa
 *
 * Created on May 9, 2018, 10:19 PM
 */

#ifndef ZELTALIB_TEXT_HPP
#define ZELTALIB_TEXT_HPP

#include <SFML/Graphics/Text.hpp>

namespace zt {
    class Text : public sf::Text {
    public:
        virtual void translated();
    };
}

#endif /* TEXT_HPP */

