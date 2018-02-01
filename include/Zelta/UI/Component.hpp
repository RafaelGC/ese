/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Component.hpp
 * Author: rafa
 *
 * Created on January 28, 2018, 11:57 PM
 */

#ifndef ZELTALIB_UI_COMPONENT_HPP
#define ZELTALIB_UI_COMPONENT_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Drawable.hpp>


namespace zt {
namespace ui {

    class Component : public sf::Drawable {
    public:
        virtual void handleEvent(const sf::Event& event) = 0;
        virtual void setAvailableArea(const sf::FloatRect& area);
        const sf::FloatRect& getAvailableArea() const;
        
    protected:
        sf::FloatRect availableArea;
    };
    
}
}

#endif /* COMPONENT_HPP */

