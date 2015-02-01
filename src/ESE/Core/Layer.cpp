#include <ESE/Core/Layer.hpp>

namespace ESE {

    Layer::Layer() {
        visible = true;
    }

    Layer::~Layer() {
    }

    void Layer::draw(sf::RenderTarget & target, sf::RenderStates states) const {
        if (!visible) {
            return;
        }

        for (auto it = drawableItems.begin(); it != drawableItems.end(); ++it) {
            sf::Drawable *d = *it;
            target.draw(*d, states);
        }
    }

    void Layer::addDrawable(sf::Drawable*item) {
        drawableItems.push_back(item);
    }

    void Layer::setVisible(bool visible) {
        this->visible = visible;
    }

}

