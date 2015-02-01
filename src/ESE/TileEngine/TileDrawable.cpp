#include <ESE/TileEngine/TileDrawable.hpp>

namespace ESE {

    TileDrawable::TileDrawable() {
        setVisibleInTilemap(true);
    }

    void TileDrawable::setVisibleInTilemap(bool visibleInTilemap) {
        this->visibleInTilemap = visibleInTilemap;
    }

    bool TileDrawable::getVisibleInTilemap() {
        return visibleInTilemap;
    }

    void TileDrawable::draw(sf::RenderTarget & target, sf::RenderStates states) const {
        if (visibleInTilemap) {
            target.draw((sf::Sprite)(*this), states);
        }
    }
}