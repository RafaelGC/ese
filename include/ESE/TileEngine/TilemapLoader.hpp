#ifndef TILEMAPLOADER_HPP
#define TILEMAPLOADER_HPP

#include <cstring>

#include <ESE/TileEngine/TileLoadedListener.hpp>
#include <ESE/External/pugixml.hpp>

#include <iostream>
#include <SFML/System/Vector2.hpp>

namespace ESE {

    /**
     * @brief Clase encargada de cargar un archivo XML con el contenido del tilemap.
     * */
    class TilemapLoader {
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
         * En este punto el tileset <b>debería tener ya una textura y un tamaño
         * de tile válido</b>.
         * */
        void loadFromFile(std::string file);

        virtual void sizeLoaded(sf::Vector2u mapSize, const sf::Vector2u& tileSize) = 0;
        virtual void layerLoaded(const std::wstring& name) = 0;
        virtual void layerFinished() = 0;
        virtual void tileLoaded(int gid, const sf::Vector2u& position) = 0;
        
        
        int getHeight();
        int getTileHeight();
        int getTileWidth();
        int getWidth();
    };

}
#endif
