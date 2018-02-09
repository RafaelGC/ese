#ifndef ZELTALIB_TEXTURECONTAINER_HPP
#define ZELTALIB_TEXTURECONTAINER_HPP

#include <SFML/Graphics.hpp>

#include <Zelta/Core/ResourceManager.hpp>

namespace zt {

    /**
     * @brief Es un contenedor de texturas que hereda de ResourceManager.
     * */
    class Textures : public zt::ResourceManager<sf::Texture>, public Singleton<Textures> {
        friend class Singleton<Textures>;
    private:
        Textures() : zt::ResourceManager<sf::Texture>("texture") {}
    public:
        virtual void loadFromFile(const std::string & name, const std::string & file) {
            if (resources[name].loadFromFile(file) == false) {
                std::cout << "Error" << std::endl;
            }
        }

    };

}

#endif // TEXTURECONTAINER_HPP
