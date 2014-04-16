#include <ESE/Core/TextureContainer.hpp>

namespace ESE
{
TextureContainer::TextureContainer():ResourceContainer()
{
}

TextureContainer::~TextureContainer()
{
}

void TextureContainer::loadFromFile(std::string name, std::string path){
	resources[name].loadFromFile(path);
}

}

