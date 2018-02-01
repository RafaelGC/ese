/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VBox.hpp
 * Author: rafa
 *
 * Created on January 29, 2018, 12:10 AM
 */

#ifndef ZELTALIB_UI_VBOX_HPP
#define ZELTALIB_UI_VBOX_HPP

#include <Zelta/UI/Layout.hpp>

namespace zt {
namespace ui {
    
    class VBox : public Layout {
    public:
        VBox();
        VBox(const VBox& orig);
        virtual ~VBox();
        
        void setSize(const sf::Vector2f& size);
        void add(Component& component);
    private:

};

}
}

#endif /* VBOX_HPP */

