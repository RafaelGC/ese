#ifndef TILEDRAWABLE_HPP
#define TILEDRAWABLE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

namespace ESE{
/**
 * @brief Es la representación gráfica de un tile. Su utilidad es la de ser dibujado en la
 * pantalla.
 * */
class TileDrawable:public sf::Sprite{
	private:
	/**
	 * @brief Si el Tile está fuera de los límites de dibujo del Tilemap establecidos por el
	 * programador, el tile no se dibujará y esta variable será puesta a false.
	 * */
	bool visibleInTilemap;
	
	public:
	TileDrawable();
	/*virtual ~TileDrawable(){

	}*/
	void setVisibleInTilemap(bool visibleInTilemap);
	bool getVisibleInTilemap();
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}

#endif
