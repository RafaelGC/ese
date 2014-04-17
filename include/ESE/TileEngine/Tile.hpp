#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
namespace ESE{
class Tile:public sf::Sprite{
	private:
	/**
	 * @brief Si el Tile está fuera de los límites de dibujo del Tilemap establecidos por el
	 * programador, el tile no se dibujará y esta variable será puesta a false.
	 * */
	bool visibleInTilemap;
	
	public:
	Tile();
	void setVisibleInTilemap(bool visibleInTilemap);
	bool getVisibleInTilemap();
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}

#endif