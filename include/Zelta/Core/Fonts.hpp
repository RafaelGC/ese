/* 
 * File:   FontContainer.hpp
 * Author: Rafa
 *
 * Created on 6 de marzo de 2015, 11:46
 */

#ifndef ZELTALIB_FONTCONTAINER_HPP
#define	ZELTALIB_FONTCONTAINER_HPP

#include <iostream>
#include <SFML/Graphics/Font.hpp>

#include <Zelta/Core/ResourceManager.hpp>
namespace zt {

    class Fonts : public zt::ResourceManager<sf::Font> {
    public:
        Fonts() : zt::ResourceManager<sf::Font>("font") {}
        virtual void loadFromFile(const std::string & name,const std::string & file) {
            if (resources[name].loadFromFile(file) == false) {
                throw FileNotFoundException();
            }
        }
        
        virtual void loadFromMemory(const std::string& name, const void* data, std::size_t size) {
            if (resources[name].loadFromMemory(data, size) == false) {
                throw FileNotFoundException();
            }
        }
    };
    
}

#endif	/* FONTCONTAINER_HPP */

