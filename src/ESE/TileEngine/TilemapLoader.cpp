#include <ESE/TileEngine/TilemapLoader.hpp>

#include "ESE/TileEngine/TilemapRenderer.hpp"

namespace ESE {

    TilemapLoader::TilemapLoader() {
        listener = nullptr;
        width = height = tileWidth = tileHeight = 0;
    }

    void TilemapLoader::setTileLoadedListener(TileLoadedListener*listener) {
        this->listener = listener;
    }

    void TilemapLoader::loadFromFile(std::string file) {
        pugi::xml_document doc;
        if (!doc.load_file(file.c_str())) {
            std::cout << "Tilemap could not be loaded." << std::endl;
        }

        //El primer nodo es el mapa, que contiene otros nodos.
        pugi::xml_node map = doc.first_child();
        //Este nodo tiene información útil como el tamaño del mapa en tiles así como el ancho y alto
        //de cada tile.
        width = map.attribute(L"width").as_int();
        height = map.attribute(L"height").as_int();
        tileWidth = map.attribute(L"tilewidth").as_int();
        tileHeight = map.attribute(L"tileheight").as_int();

        //tilemapRenderer.setSize(sf::Vector2u(width, height));
        this->sizeLoaded(sf::Vector2u(width, height), sf::Vector2u(tileWidth, tileHeight));
        
        if (listener) {
            listener->onInfoLoaded(tileWidth, tileHeight, width, height);
        }

        //Ahora recorreremos los nodos del mapa en busca de los que nos interesan.
        for (pugi::xml_node node = map.first_child(); node; node = node.next_sibling()) {
            //La capa es el elemento más importante, por ahora sólo soportamos una.
            if (wcscmp(node.name(), L"layer") == 0) {
                //Dentro de la capa hay un elemento "data" que a su vez contiene un motón de
                //nodos "tile" cuyos valores son los que nos interesan.
                
                
                this->layerLoaded(node.attribute(L"name").as_string());
                
                pugi::xml_node nodoData = node.first_child();
                if (wcscmp(nodoData.name(), L"data") == 0) {

                    int auxX = 0, auxY = 0;
                    //Ahora recorremos, dentro de data, todos los tiles.
                    for (pugi::xml_node nodoTiles = nodoData.first_child(); nodoTiles; nodoTiles = nodoTiles.next_sibling()) {
                        int type = nodoTiles.attribute(L"gid").as_int();
                        
                        
                        if (type != 0) {
                            this->tileLoaded(type, sf::Vector2u(auxX, auxY));
                        }
                        //std::cout << auxX << ", " << auxY << std::endl;
                        auxX++;
                        if (auxX > width - 1) {
                            auxX = 0;
                            auxY++;
                        }
                    }

                }
                
                this->layerFinished();

            } else if (wcscmp(node.name(), L"objectgroup") == 0) {
                //Dentro del nodo objectgroup hay un montón de objetos que nos interesan.
                for (pugi::xml_node nodeObjects = node.first_child(); nodeObjects; nodeObjects = nodeObjects.next_sibling()) {
                    //std::cout << "Tipo: " << nodeObjects.attribute("type").as_string("ESE::Error") << std::endl;
                    if (listener) {
                        listener->onObjectLoaded(nodeObjects.attribute(L"x").as_float(0), nodeObjects.attribute(L"y").as_float(0),
                                nodeObjects.attribute(L"type").as_string(L"ESE::Error"), nodeObjects.attribute(L"name").as_string(L"ESE::Error"));
                    }
                }
            } else if (wcscmp(node.name(), L"properties") == 0) {
                for (pugi::xml_node nodeProperty = node.first_child(); nodeProperty; nodeProperty = nodeProperty.next_sibling()) {
                    if (listener) {
                        listener->onPropertyLoaded(nodeProperty.attribute(L"name").as_string(L"ESE::Error"), nodeProperty.attribute(L"value").as_string(L"ESE::Error"));
                    }
                }
            }


        }

    }

    int TilemapLoader::getHeight() {
        return height;
    }

    int TilemapLoader::getTileHeight() {
        return tileHeight;
    }

    int TilemapLoader::getTileWidth() {
        return tileWidth;
    }

    int TilemapLoader::getWidth() {
        return width;
    }

}