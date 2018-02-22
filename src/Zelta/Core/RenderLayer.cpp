#include <Zelta/Core/RenderLayer.hpp>

namespace zt {

    RenderLayer::RenderLayer(bool visible) {
        this->visible = visible;
    }

    RenderLayer::~RenderLayer() {
    }

    void RenderLayer::draw(sf::RenderTarget & target, sf::RenderStates states) const {
        if (!visible) {
            return;
        }

        for (auto it = drawableItems.begin(); it != drawableItems.end(); ++it) {
            sf::Drawable *d = *it;
            target.draw(*d, states);
        }
    }

    void RenderLayer::addDrawable(sf::Drawable &item) {

        for (auto i : drawableItems) {
            if (i == &item) return;
        }

        drawableItems.push_back(&item);
    }

    bool RenderLayer::removeDrawable(sf::Drawable& item) {
        for (auto it = drawableItems.begin(); it != drawableItems.end(); ++it) {
            if (*it == &item) {
                drawableItems.erase(it);
                return true;
            }
        }
        return false;
    }

    void RenderLayer::setVisible(bool visible) {
        this->visible = visible;
    }

    bool RenderLayer::isVisible() const {
        return visible;
    }

    unsigned int RenderLayer::count() const {
        return drawableItems.size();
    }
    
    bool RenderLayer::isEmpty() const {
        return count()==0;
    }

}

