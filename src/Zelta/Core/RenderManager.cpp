/* 
 * File:   RenderManager.cpp
 * Author: Rafa
 * 
 * Created on 29 de agosto de 2015, 19:59
 */

#include <Zelta/Core/RenderManager.hpp>

namespace zt {

    RenderManager::RenderManager() {
    }

    RenderManager::~RenderManager() {
    }

    void RenderManager::addDrawable(sf::Drawable& drawable, int z) {

        zt::Layer newLayer(z,true);
        newLayer.addDrawable(drawable);


        for (auto it = layers.begin(); it!=layers.end(); ++it) {

            if (z<it->getZ()) {
                layers.insert(it,newLayer);
                return;
            }
            else if (z==it->getZ()) {
                it->addDrawable(drawable);
                return;
            }
        }

        layers.push_back(newLayer);
    }

    void RenderManager::removeDrawable(sf::Drawable& drawable) {
        for (auto it = layers.begin(); it!=layers.end(); ++it) {
            if (it->removeDrawable(drawable)) {

                if (it->isEmpty()) {
                    layers.erase(it);
                }
                return;
            }
        }
    }

    void RenderManager::moveDrawable(sf::Drawable& drawable, int newZ) {
        removeDrawable(drawable);
        addDrawable(drawable,newZ);
    }

    void RenderManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (auto & it : layers) {
            target.draw(it, states);
        }
    }

}