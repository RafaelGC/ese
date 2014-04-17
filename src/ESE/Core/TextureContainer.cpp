#include <ESE/Core/TextureContainer.hpp>

namespace ESE
{
TextureContainer::TextureContainer():ResourceContainer()
{
}

TextureContainer::~TextureContainer()
{
}

void TextureContainer::loadFromFile(std::string name, std::string file){
	if (resources[name].loadFromFile(file)==false){
		std::cout << "Error" << std::endl;
	}
}

}

