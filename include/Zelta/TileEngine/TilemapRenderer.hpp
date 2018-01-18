#ifndef TILEMAPRENDERER_HPP
#define TILEMAPRENDERER_HPP

#include <cstring>
#include <iostream>

#include <SFML/Graphics/Drawable.hpp>

#include <Zelta/External/pugixml.hpp>
#include <Zelta/TileEngine/TileSprite.hpp>
#include <Zelta/TileEngine/TilemapLayer.hpp>
#include <iostream>

namespace zt {

    template <class T>
    class TilemapRenderer : public sf::Drawable {
    protected:
        
        /**
         * @brief Ancho y alto en tiles del mapa.
         * */
        sf::Vector2u size;
        /**
         * @brief Ancho y alto de cata tile.
         * */
        sf::Vector2u tileSize;
        
        Tileset* tileset;
        
        std::vector<TilemapLayer<T>> layers;
        
        sf::View view;

    public:

        TilemapRenderer() {
            tileset = nullptr;
        }

        ~TilemapRenderer() {
        }
        
        void setSize(const sf::Vector2u& size) {
            this->size = size;
        }
        
        const sf::Vector2u& getSize() const {
            return size;
        }
        
        /**
         * @brief Permite seleccionar el tileset que se utilizará para renderizar los tiles.
         * */
        void setTileset(Tileset& tileset) {
            this->tileset = &tileset;
        }
        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            for (const TilemapLayer<T>& layer : layers) {
                layer.draw(target, states);
            }
        }

        virtual void addLayer(TilemapLayer<T> layer) {
            this->layers.push_back(layer);
        }

        void updateView(const sf::View& view) {
            this->view = view;
            for (TilemapLayer<T>& layer : layers) {
                layer.updateView(view);
            }
        }
        
        /**
         * Devuelve una capa a partir de su nombre. Si no existe
         * lanza una excepción.
         * @param name
         * @return Capa.
         */
        TilemapLayer<T>& getLayerByName(std::wstring name) {
            for (auto& layer : layers) {
                if (layer.getName() == name) {
                    return layer;
                }
            }
            
            throw std::exception();
        }

    };

}
#endif