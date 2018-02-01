/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Layout.hpp
 * Author: rafa
 *
 * Created on January 28, 2018, 11:47 PM
 */

#ifndef ZELTALIB_UI_LAYOUT_HPP
#define ZELTALIB_UI_LAYOUT_HPP

#include <Zelta/UI/Component.hpp>

#include <vector>

namespace zt {
namespace ui {

    class Layout : public Component {
    public:
        void add(Component& component);
        
    protected:
        std::vector<Component*> components;
    };
    
}    
}

#endif /* LAYOUT_HPP */

