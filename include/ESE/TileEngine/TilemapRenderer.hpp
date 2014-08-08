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
	/**
	 * @brief Permite seleccionar el tileset que se utilizará para renderizar los tiles.
	 * */
	void setTileset(sf::Texture *tileset);
	/**
	 * @brief Cada tipo de tile, representado con un número entero, tiene relacionado un
	 * trozo de imagen extraido del tileset. Mediante esta función establecemos qué trozo
	 * de imagen se relacionará con cada tipo de tile.
	 * @param number El identificador del tile al que queremos relacionar con el trozo de imagen.
	 * @param rect Mediante rect delimitamos el trozo de imagen que queremos relacionar con el
	 * tipo de tile.
	 * */
	void setTilesetCoords(int number, sf::IntRect rect);
	/**
	 * @brief Este método permite establecer los distintos trozos de imagen conociendo únicamente
	 * el ancho y alto de cada tile, de tal modo que nos ahorrará el esfuerzo de llamar al método
	 * setTilesetCoords(). <b>Si llamamos a este método no es necesario llamar a setTileDimensions()</b>
	 * */
	void detectTilesetCoords(int tileWidth, int tileHeight);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	/**
	 * @brief Permite elegir a partir de dónde se comenzará a dibujar el mapa.
	 * */
	void setOriginOfMap(float x, float y);
	/**
	 * @brief Permite establecer los límites de dibujo para optimizar el rendimiento.
	 * */
	void setRenderingLimits(float x, float y, float width, float height);
	/**
	 * @brief Este método sirve para especificar el ancho y alto, en píxeles, de cada
	 * tile. <b>Es importante</b> hacer esto antes de añadir algún tile al tilemap, pues
	 * para calcular la posición de cada tile es necesario conocer su ancho y alto. También
	 * cabe mencionar que si llamamos al método detectTilesetCoords() no es necesario llamar
	 * a este método.
	 * */
	void setTileDimensions(int tileWidth, int tileHeight);
	/**
	 * @brief Permite añadir un tile de cierto tipo y en cierta posición.
	 * @param type Tipo de tile.
	 * @param colX Posición horizontal, <b>en casillas</b> (no en píxeles), del tile.
	 * @param colY Posición vertical, <b>en casillas</b> (no en píxeles), del tile.
	 * @return Posición del tile insertado dentro del array de tiles. Puede ser útil para acceder
	 * a él más tarde. Puntero a dicho tile.
	 * */
	std::pair<int, ESE::TileDrawable*> addTile(int type, int colX, int rowY);
	/**
	 * Este método sirve para obtener un cierto tile.
	 * @param Posición del tile que queremos obtener dentro del array.
	 * @return Puntero al tile que hay en la posición especificada.
	 * */
	ESE::TileDrawable* tileAt(int index);
	sf::Vector2f getOriginOfMap();
	
};

}
#endif