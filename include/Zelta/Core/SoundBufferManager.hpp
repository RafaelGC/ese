#ifndef SOUNDCONTAINER_HPP
#define SOUNDCONTAINER_HPP

#include <SFML/Audio/SoundBuffer.hpp>
#include <iostream>

#include <Zelta/Core/ResourceManager.hpp>

namespace zt {

    /**
     * @brief Resource manager for sf::SoundBuffer.
     * */
    class SoundBufferManager : public ResourceManager<sf::SoundBuffer> {
    public:
        SoundBufferManager() : zt::ResourceManager<sf::SoundBuffer>("sound") {}
        virtual void loadFromFile(const std::string & name,const std::string & file) {
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
#endif