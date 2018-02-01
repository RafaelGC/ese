/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <Zelta/UI/VBox.hpp>

namespace zt {
namespace ui {
    
    VBox::VBox() {
    }
    
    VBox::VBox(const VBox& orig) {
    }
    
    VBox::~VBox() {
    }
    
    void VBox::add(Component& component) {
        Layout::add(component);
        
        float w = this->getAvailableArea().width / components.size();
        float h = this->getAvailableArea().height;
        float x = 0;
        
        for (Component* l : components) {
            l->setAvailableArea(sf::FloatRect(x, 0, w, h));
        }
    }

}
}