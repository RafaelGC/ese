/* 
 * File:   FontContainer.hpp
 * Author: Rafa
 *
 * Created on 6 de marzo de 2015, 11:46
 */

#ifndef ESE_FONTCONTAINER_HPP
#define	ESE_FONTCONTAINER_HPP

#include <iostream>
#include <SFML/Graphics/Font.hpp>

#include <ESE/Core/ResourceContainer.hpp>
namespace ESE {

    class FontContainer : public ESE::ResourceContainer<sf::Font> {
    public:
        FontContainer();
        virtual ~FontContainer();
        virtual void loadFromFile(std::string name, std::string path);
    };
    
}

#endif	/* FONTCONTAINER_HPP */

