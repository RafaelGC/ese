#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include "TextureContainer.hpp"
namespace ESE{
class ResourceManager
{
	static ResourceManager* resourceManagerInstance;
protected:
	ESE::TextureContainer textureContainer;
public:
	static ResourceManager* instance();
	static void release();
	
	ESE::TextureContainer *getTextureContainer();

private:
	ResourceManager();
	virtual ~ResourceManager();

};
}
#endif // RESOURCES_HPP
