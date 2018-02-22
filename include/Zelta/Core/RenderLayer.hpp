#ifndef ZELTALIB_LAYER_HPP
#define ZELTALIB_LAYER_HPP

#include <vector>

#include <SFML/Graphics/Drawable.hpp> // Base class: sf::Drawable
#include <SFML/Graphics/RenderTarget.hpp>

namespace zt {

    /**
     * @brief Container for drawable objects.
     * This class allows you to group sf::Drawable elements such as sf::Sprite.
     * The container keeps pointers to the objects, so your drawable objects
     * should be kept alive while using the render layer.
     * */
    class RenderLayer : public sf::Drawable {
    protected:
        /**
         * @brief If it's false the contained objects won't be drawn.
         * */
        bool visible;
        /**
         * @brief Vector que contiene un puntero a los dibujables de esta capa.
         * */
        std::vector<sf::Drawable*>drawableItems;

    public:
        /**
         * @brief Constructs an empty layer.
         * */
        RenderLayer(bool visible = true);
        
        virtual ~RenderLayer();
        /**
         * @brief Draws all contained objects if the layer is visible.
         * */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        
        /**
         * @brief Adds a drawable.
         * */
        void addDrawable(sf::Drawable &item);
        
        /**
         * @brief Removes a drawable if it exists.
         * @param item Drawable you cant to remove.
         * @return True if it was removed.
         */
        bool removeDrawable(sf::Drawable & item);
        
        /**
         * @brief Sets the visibility.
         * */
        void setVisible(bool visible);
        bool isVisible() const;
        
        int getZ() const;
        void setZ(int z);
        
        unsigned int count() const;
        bool isEmpty() const;
        
        /**
         * Compares the depth of the layer.
         * @param other
         * @return 
         */
        bool operator<(zt::RenderLayer & other) const;

    };

}

#endif // LAYER_HPP
