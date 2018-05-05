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
        TilemapLayer() { }
        
        
        void setSize(const sf::Vector2u& size) {
            this->size = size;
            tiles.resize(size.x * size.y);
        }
        
        const sf::Vector2u& getSize() const {
            return size;
        }
        
        void setTileSize(const sf::Vector2u& tileSize) {
            this->tileSize = tileSize;
        }
        
        const sf::Vector2u& getTileSize() const {
            return tileSize;
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
        
        std::pair<int, T*> addTile(const T& tile, const sf::Vector2u& tilePosition) {
            TileContainer<T> tmp;
            tmp.tile = tile;
            tmp.tile.setPosition((int)(tilePosition.x * tileSize.x), (int)(tilePosition.y * tileSize.y));
            tmp.empty = false;
            
            tiles[tilePosition.x + tilePosition.y * size.x] = tmp;
            return std::make_pair(tiles.size() - 1, &tiles[tilePosition.x + tilePosition.y * size.x].tile);
        }
        
        /**
         * @brief Add a tile in a given position.
         * @param tilePosition Position (measured in tiles).
         * @return Returns a pair. The first element is the position of the tile
         * in the vector. The second element is a pointer to the new tile.
         * */
        std::pair<int, T*> addTile(const sf::Vector2u& tilePosition) {
            TileContainer<T> tmp;
            tmp.tile.setPosition((int)(tilePosition.x * tileSize.x), (int)(tilePosition.y * tileSize.y));
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
            return tiles[x + y * size.x].tile;
        }
        
    private:
        std::vector<TileContainer<T>> tiles;
        sf::View view;
        std::wstring name;
        sf::Vector2u size, tileSize;
    };
}

#endif /* TILEMAPLAYER_HPP */

