/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <Zelta/UI/Layout.hpp>
#include <vector>


namespace zt {
namespace ui {

    void Layout::add(Component& component) {
        components.push_back(&component);
    }
    
    
}
}