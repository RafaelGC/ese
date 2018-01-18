#include <Zelta/Core/Layer.hpp>

namespace zt {

    Layer::Layer() {
        visible = true;
    }

    Layer::Layer(int z, bool visible) {
        this->z = z;
        this->visible = true;
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

    void Layer::addDrawable(sf::Drawable &item) {

        for (auto i : drawableItems) {
            if (i == &item) return;
        }

        drawableItems.push_back(&item);
    }

    bool Layer::removeDrawable(sf::Drawable& item) {
        for (auto it = drawableItems.begin(); it != drawableItems.end(); ++it) {
            if (*it == &item) {
                drawableItems.erase(it);
                return true;
            }
        }
        return false;
    }

    void Layer::setVisible(bool visible) {
        this->visible = visible;
    }

    bool Layer::isVisible() const {
        return visible;
    }

    int Layer::getZ() const {
        return z;
    }

    void Layer::setZ(int z) {
        this->z = z;
    }
    
    unsigned int Layer::count() const {
        return drawableItems.size();
    }
    
    bool Layer::isEmpty() const {
        return count()==0;
    }

    bool Layer::operator<(zt::Layer& other) const {
        return getZ() < other.getZ();
    }

}

