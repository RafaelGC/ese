/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TilemapLayer.hpp
 * Author: rafa
 *
 * Created on January 10, 2018, 8:52 PM
 */

#ifndef ZELTALIB_TILEMAPLAYER_HPP
#define ZELTALIB_TILEMAPLAYER_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <Zelta/TileEngine/Tileset.hpp>

namespace zt {
    
    template <class T>
    class TileContainer {
    public:
        T tile;
        bool empty;
        
        TileContainer() {
            empty = true;
        }
    };
    
    template <class T>
    class TilemapLayer : public sf::Drawable {
    public:
        TilemapLayer() { tileset = nullptr; }
        
        TilemapLayer(const Tileset& tileset) : tileset(&tileset) {
        }
        
        void setSize(const sf::Vector2u& size) {
            this->size = size;
            tiles.resize(size.x * size.y);
        }
        
        void updateView(const sf::View& view) {
            this->view = view;
        }
        
        void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            for (const TileContainer<T>& tc : tiles) {
                if (tc.empty == false) {
                    if (tc.tile.getPosition().x + tc.tile.getSize().x < view.getCenter().x - view.getSize().x / 2) { continue; }
                    if (tc.tile.getPosition().x > view.getCenter().x + view.getSize().x / 2) { continue; }
                    if (tc.tile.getPosition().y + tc.tile.getSize().y < view.getCenter().y - view.getSize().y / 2) { continue; }
                    if (tc.tile.getPosition().y > view.getCenter().y + view.getSize().y / 2) { continue; }

                    target.draw(tc.tile, states);
                }
            }
        }
        
        /**
         * @brief Permite añadir un tile de cierto tipo y en cierta posición.
         * @param type Tipo de tile.
         * @param tilePosition Posición <b>medida en tiles</b> del tile que se añade.
         * @return El métdoo devuelve un std::pair cuyo primer elemento es la posición
         * en el vector del tile que acabamos de añadir y un puntero a dicho tile.
         * */
        std::pair<int, T*> addTile(int type, const sf::Vector2u& tilePosition) {
            TileContainer<T> tmp;
            const sf::Texture& tex = tileset->getTextureForTile(type);
            tmp.tile.setTexture(tileset->getTextureForTile(type));
            tmp.tile.setPosition((int)(tilePosition.x * tex.getSize().x), (int)(tilePosition.y * tex.getSize().y));
            tmp.empty = false;
            
            tiles[tilePosition.x + tilePosition.y * size.x] = tmp;
            return std::make_pair(tiles.size() - 1, &tiles[tilePosition.x + tilePosition.y * size.x].tile);
        }
        
        unsigned int countTiles() const {
            return tiles.size();
        }
        
        void setName(const std::wstring& name) {
            this->name = name;
        }
        
        const std::wstring& getName() const {
            return name;
        }
        
        bool isEmpty(int x, int y) {
            return tiles[x + y * size.x].empty;
        }
        
        T& getTile(int x, int y) {
            return tiles[x + y * size.y].tile;
        }
        
    private:
        std::vector<TileContainer<T>> tiles;
        sf::View view;
        const Tileset* tileset;
        std::wstring name;
        sf::Vector2u size;
    };
}

#endif /* TILEMAPLAYER_HPP */

