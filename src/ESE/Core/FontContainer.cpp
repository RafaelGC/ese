#include <ESE/Core/FontContainer.hpp>

namespace ESE{
    FontContainer::FontContainer(){
        
    }
    
    FontContainer::~FontContainer(){
        
    }
    
    void FontContainer::loadFromFile(std::string name, std::string path){
        if (resources[name].loadFromFile(path)==false){
            std::cout << "Error al cargar una fuente." << std::endl;
        }
    }
}
