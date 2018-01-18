#ifndef SOUNDCONTAINER_HPP
#define SOUNDCONTAINER_HPP

#include <SFML/Audio/SoundBuffer.hpp>
#include <iostream>

#include <Zelta/Core/ResourceManager.hpp>

namespace zt {

    class SoundBuffers : public ResourceManager<sf::SoundBuffer>, public Singleton<SoundBuffers> {
        friend class Singleton<SoundBuffers>;
    private:
        SoundBuffers() : zt::ResourceManager<sf::SoundBuffer>("sound") {}
    public:
        virtual void loadFromFile(const std::string & name,const std::string & file) {
            if (resources[name].loadFromFile(file) == false) {
                std::cout << "Error" << std::endl;
            }
        }
    };

}
#endif