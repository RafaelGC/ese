#ifndef TILEMAPLOADER_HPP
#define TILEMAPLOADER_HPP

#include <cstring>

#include <ESE/TileEngine/TileLoadedListener.hpp>
#include <ESE/External/pugixml.hpp>

namespace ESE
{
/**
 * @brief Clase encargada de cargar un archivo XML con el contenido del tilemap.
 * */
class TilemapLoader
{
	private:
	/**
	 * @brief Listener cuyos métodos son llamados bajo ciertas circunstancias durante
	 * la carga del mapa para informar al programador.
	 * */
	ESE::TileLoadedListener *listener;
	
	/**
	 * @brief Tamaño, en casillas, del mapa.
	 * */
	int width, height;
	/**
	 * @brief Tamaño, en píxeles, de cada casilla del mapa.
	 * */
	int tileWidth, tileHeight;

public:
	TilemapLoader();
	/**
	 * @brief Permite elegir el objeto que implementa los métodos puros del listener
	 * y que será informado de los eventos ocurridos.
	 * */
	void setTileLoadedListener(TileLoadedListener*listener);
	/**
	 * @brief Carga el mapa desde un fichero XML.
	 * El método infoLoaded() del listener es
	 * ejecutado cuando se encuentra información útil como el tamaño del mapa y el de
	 * los  tiles. Esto puede ser útil porque el programador necesitará de estos datos antes
	 * de añadir nada al TilemapRenderer.
	 * También se llama desde aquí al método tileLoaded() cada vez que se encuentra un
	 * tile, pasándole como parámetro la posición x e y (en casillas) del tile que se ha encontrado
	 * así como el número que lo identifica.
	 * */
	void loadFromFile(std::string file);
	
	int getHeight();
	int getTileHeight();
	int getTileWidth();
	int getWidth();
};

}
#endif
