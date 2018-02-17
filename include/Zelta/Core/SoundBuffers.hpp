#ifndef SOUNDCONTAINER_HPP
#define SOUNDCONTAINER_HPP

#include <SFML/Audio/SoundBuffer.hpp>
#include <iostream>

#include <Zelta/Core/ResourceManager.hpp>

namespace zt {

    class SoundBuffers : public ResourceManager<sf::SoundBuffer> {
    public:
        SoundBuffers() : zt::ResourceManager<sf::SoundBuffer>("sound") {}
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
#endif