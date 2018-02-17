#ifndef ZELTALIB_TEXTURECONTAINER_HPP
#define ZELTALIB_TEXTURECONTAINER_HPP

#include <SFML/Graphics.hpp>

#include <Zelta/Core/ResourceManager.hpp>

namespace zt {

    /**
     * @brief Es un contenedor de texturas que hereda de ResourceManager.
     * */
    class Textures : public zt::ResourceManager<sf::Texture> {
    public:
        Textures() : zt::ResourceManager<sf::Texture>("texture") {}
        virtual void loadFromFile(const std::string & name, const std::string & file) {
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

#endif // TEXTURECONTAINER_HPP
