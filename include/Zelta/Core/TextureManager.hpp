#ifndef ZELTALIB_TEXTURECONTAINER_HPP
#define ZELTALIB_TEXTURECONTAINER_HPP

#include <SFML/Graphics.hpp>

#include <Zelta/Core/ResourceManager.hpp>

namespace zt {

    /**
     * @brief Resource manager for sf::Texture.
     * */
    class TextureManager : public zt::ResourceManager<sf::Texture> {
    public:
        TextureManager() : zt::ResourceManager<sf::Texture>("texture") {}
        virtual void loadFromFile(const std::string & name, const std::string & file) {
            if (resources[name].resource.loadFromFile(file) == false) {
                throw FileNotFoundException();
            }
        }
        
        virtual void loadFromMemory(const std::string& name, const void* data, std::size_t size) {
            if (resources[name].resource.loadFromMemory(data, size) == false) {
                throw FileNotFoundException();
            }
        }
        
    };

}

#endif // TEXTURECONTAINER_HPP
