#ifndef TILEMAPRENDERER_HPP
#define TILEMAPRENDERER_HPP

#include <cstring>
#include <iostream>

#include <SFML/Graphics/Drawable.hpp>

#include <ESE/External/pugixml.hpp>
#include <ESE/TileEngine/TileDrawable.hpp>

namespace ESE{
class TilemapRenderer:public sf::Drawable{
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
	sf::FloatRect renderingLimits;
	std::vector<ESE::TileDrawable>tiles;
	public:
	TilemapRenderer();
	void setTileset(sf::Texture *tileset);
	void setTilesetCoords(int number, sf::IntRect rect);
	void detectTilesetCoords(int tileWidth, int tileHeight);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setOriginOfMap(float x, float y);
	void setRenderingLimits(float x, float y, float width, float height);
	void setTileDimensions(int tileWidth, int tileHeight);
	int addTile(int type, int colX, int rowY);
	ESE::TileDrawable* tileAt(int index);
	sf::Vector2f getOriginOfMap();
	
};

}
#endif