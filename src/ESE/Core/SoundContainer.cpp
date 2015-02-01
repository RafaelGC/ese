#include <ESE/Core/SoundContainer.hpp>

namespace ESE {

    SoundContainer::SoundContainer() : ResourceContainer() {

    }

    void SoundContainer::loadFromFile(std::string name, std::string file) {
        if (resources[name].loadFromFile(file) == false) {
            std::cout << "Error" << std::endl;
        }

    }

}