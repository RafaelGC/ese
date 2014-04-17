#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <cstring>
#include <iostream>

#include <SFML/Graphics/Drawable.hpp>

#include <ESE/External/pugixml.hpp>
#include <ESE/TileEngine/Tile.hpp>

namespace ESE{
class Tilemap:public sf::Drawable{
	protected:
	sf::Texture *tileset;
	std::map<int,sf::IntRect>rects;
	float originX, originY;
	/**
	 * @brief Ancho y alto en tiles del mapa.
	 * */
	int width, height;
	/**
	 * @brief Ancho y alto de cata tile.
	 * */
	int tileWidth, tileHeight;
	
	std::vector<ESE::Tile>tiles;
	public:
	Tilemap();
	void setTileset(sf::Texture *tileset);
	void setTilesetCoords(int number, sf::IntRect rect);
	void load(std::string file);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setOriginOfMap(float x, float y);
	
	sf::Vector2f getOriginOfMap();
	
};

}
#endif