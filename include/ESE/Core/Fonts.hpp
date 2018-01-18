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

#include <ESE/Core/ResourceManager.hpp>
namespace ESE {

    class Fonts : public ESE::ResourceManager<sf::Font>, public ESE::Singleton<Fonts> {
        friend class Singleton;
    private:
        Fonts() : ESE::ResourceManager<sf::Font>("font") {}
    public:
        virtual void loadFromFile(const std::string & name,const std::string & file) {
            if (resources[name].loadFromFile(file) == false) {
                std::cout << "Error" << std::endl;
            }
        }
    };
    
}

#endif	/* FONTCONTAINER_HPP */

