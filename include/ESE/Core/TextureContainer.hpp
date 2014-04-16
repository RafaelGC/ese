#ifndef TEXTURECONTAINER_HPP
#define TEXTURECONTAINER_HPP

#include <SFML/Graphics.hpp>

#include <ESE/Core/Config.hpp>
#include <ESE/Core/ResourceContainer.hpp>
#include <ESE/Core/Log.hpp>

#include <iostream>

namespace ESE
{

class TextureContainer:public ResourceContainer<sf::Texture>
{
public:
	TextureContainer();
	virtual ~TextureContainer();
	virtual void loadFromFile(std::string name, std::string path);

};

}

#endif // TEXTURECONTAINER_HPP
