#ifndef SOUNDCONTAINER_HPP
#define SOUNDCONTAINER_HPP

#include <SFML/Audio/SoundBuffer.hpp>
#include <iostream>

#include <ESE/Core/ResourceContainer.hpp>

namespace ESE {

    class SoundContainer : public ResourceContainer<sf::SoundBuffer> {
    public:
        SoundContainer();
        void loadFromFile(std::string name, std::string path);
    };

}
#endif