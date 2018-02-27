#ifndef ZELTALIB_FONTCONTAINER_HPP
#define	ZELTALIB_FONTCONTAINER_HPP

#include <iostream>
#include <SFML/Graphics/Font.hpp>

#include <Zelta/Core/ResourceManager.hpp>
namespace zt {

    /**
     * @brief Resource manager for sf::Font.
     * */
    class FontManager : public zt::ResourceManager<sf::Font> {
    public:
        FontManager() : zt::ResourceManager<sf::Font>("font") { }
        virtual void loadFromFile(const std::string & name, const std::string & file) {
            if (resources[name].resource.loadFromFile(file) == false) {
                throw FileNotFoundException();
            }
            resources[name].isPendant = false;
        }
        
        virtual void loadFromMemory(const std::string& name, const void* data, std::size_t size) {
            if (resources[name].resource.loadFromMemory(data, size) == false) {
                throw FileNotFoundException();
            }
            resources[name].isPendant = false;
        }
        
    };
    
}

#endif	/* FONTCONTAINER_HPP */

