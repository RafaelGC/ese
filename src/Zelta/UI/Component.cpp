/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Zelta/UI/Component.hpp"


namespace zt {
namespace ui {

    void Component::setAvailableArea(const sf::FloatRect& area) {
        this->availableArea = area;
    }
    
    const sf::FloatRect& Component::getAvailableArea() const {
        return this->availableArea;
    }
}
}