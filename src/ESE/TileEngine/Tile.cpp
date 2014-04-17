#include <ESE/TileEngine/Tile.hpp>

namespace ESE{
	Tile::Tile(){
		setVisibleInTilemap(true);
	}
	void Tile::setVisibleInTilemap(bool visibleInTilemap){
		this->visibleInTilemap = visibleInTilemap;
	}
	
	bool Tile::getVisibleInTilemap(){
		return visibleInTilemap;
	}
	
	void Tile::draw(sf::RenderTarget & target, sf::RenderStates states) const{
		if (visibleInTilemap){
			target.draw((sf::Sprite)(*this),states);
		}
	}
}