/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TiledLoader.cpp
 * Author: rafa
 * 
 * Created on January 14, 2018, 8:33 PM
 */

#include <ESE/TileEngine/TiledLoader/TiledLoader.hpp>

#include <ESE/External/pugixml.hpp>
#include <ESE/TileEngine/TiledLoader/Map.hpp>
#include <ESE/TileEngine/TiledLoader/FileNotFoundException.hpp>

#include <iostream>

namespace ESE {
    namespace Tiled {
        TiledLoader::TiledLoader() {
        }

        TiledLoader::~TiledLoader() {
        }
        
        Map TiledLoader::loadFromFile(const std::string& file) {
            pugi::xml_document doc;
            if (!doc.load_file(file.c_str())) {
                throw FileNotFoundException();
            }

            //El primer nodo es el mapa, que contiene otros nodos.
            pugi::xml_node mapNode = doc.first_child();
            //Este nodo tiene información útil como el tamaño del mapa en tiles así como el ancho y alto
            //de cada tile.
            int width = mapNode.attribute(L"width").as_int();
            int height = mapNode.attribute(L"height").as_int();
            int tileWidth = mapNode.attribute(L"tilewidth").as_int();
            int tileHeight = mapNode.attribute(L"tileheight").as_int();
            std::wstring sOrientation = mapNode.attribute(L"orientation").as_string(L"orthogonal");
            
            Map::Orientation orientation;
            if (sOrientation == L"orthogonal") {
                orientation = Map::Orientation::Orthogonal;
            }
            else if (sOrientation == L"isometric") {
                orientation = Map::Orientation::Isometric;
            }
            else if (sOrientation == L"staggered") {
                orientation = Map::Orientation::Staggered;
            }
            else if (sOrientation == L"hexagonal") {
                orientation = Map::Orientation::Hexagonal;
            }
            
            this->sizeLoaded(sf::Vector2u(width, height), sf::Vector2u(tileWidth, tileHeight));
            
            Map map(width, height, tileWidth, tileHeight, orientation);

            //Ahora recorreremos los nodos del mapa en busca de los que nos interesan.
            for (pugi::xml_node node = mapNode.first_child(); node; node = node.next_sibling()) {
                if (wcscmp(node.name(), L"layer") == 0) {
                    //Dentro de la capa hay un elemento "data" que a su vez contiene un motón de
                    //nodos "tile" cuyos valores son los que nos interesan.
                    
                    int lWidth = node.attribute(L"width").as_int();
                    int lHeight = node.attribute(L"height").as_int();
                    std::wstring name = node.attribute(L"name").as_string();
                    
                    Layer layer(name, lWidth, lHeight);


                    pugi::xml_node nodoData = node.first_child();
                    if (wcscmp(nodoData.name(), L"data") == 0) {
                        
                        //int auxX = 0, auxY = 0;
                        //Ahora recorremos, dentro de data, todos los tiles.
                        for (pugi::xml_node nodoTiles = nodoData.first_child(); nodoTiles; nodoTiles = nodoTiles.next_sibling()) {
                            int gid = nodoTiles.attribute(L"gid").as_int();
                            layer.addTile(Tile(gid));
                        }

                    }
                    
                    this->layerLoaded(layer);
                    
                    map.addLayer(layer);

                } else if (wcscmp(node.name(), L"objectgroup") == 0) {
                    ObjectLayer layer(node.attribute(L"name").as_string());
                    for (pugi::xml_node nodeObjects = node.first_child(); nodeObjects; nodeObjects = nodeObjects.next_sibling()) {
                        int id = nodeObjects.attribute(L"id").as_int(0);
                        int x = nodeObjects.attribute(L"x").as_int(0);
                        int y = nodeObjects.attribute(L"y").as_int(0);
                        std::wstring name = nodeObjects.attribute(L"name").as_string();
                        std::wstring type = nodeObjects.attribute(L"type").as_string();
                        
                        pugi::xml_attribute attr;
                        if (attr = nodeObjects.attribute(L"gid")) {
                            layer.addObject(Object(id, name, type, x, y, attr.as_int()));
                        }
                        else {
                            layer.addObject(Object(id, name, type, x, y));
                        }
                        
                    }
                    map.addObjectLayer(layer);
                    this->objectLayerLoaded(layer);
                    
                } else if (wcscmp(node.name(), L"properties") == 0) {
                    /*
                    for (pugi::xml_node nodeProperty = node.first_child(); nodeProperty; nodeProperty = nodeProperty.next_sibling()) {
                        if (listener) {
                            listener->onPropertyLoaded(nodeProperty.attribute(L"name").as_string(L"ESE::Error"), nodeProperty.attribute(L"value").as_string(L"ESE::Error"));
                        }
                    }
                    */
                }


            }
            
            return map;
        }
    }
}

