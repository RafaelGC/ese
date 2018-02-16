/* 
 * File:   RenderManager.hpp
 * Author: Rafa
 *
 * Created on 29 de agosto de 2015, 19:59
 */

#ifndef RENDERMANAGER_HPP
#define	RENDERMANAGER_HPP

#include <queue>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <Zelta/Core/RenderLayer.hpp>

namespace zt {
    /**
     * @brief Esta clase permite organizar el dibujado de objetos en función de
     * su profundidad.
     */
    class RenderManager : public sf::Drawable{
    public:
        RenderManager();
        virtual ~RenderManager();

        void addDrawable(sf::Drawable & drawable, int z = 0);
        void removeDrawable(sf::Drawable & drawable);
        void moveDrawable(sf::Drawable & drawable, int newZ);

        void draw(sf::RenderTarget & target, sf::RenderStates states) const;
    private:
        std::vector<zt::RenderLayer> layers;
    };

}

#endif	/* RENDERMANAGER_HPP */

