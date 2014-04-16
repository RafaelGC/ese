#include <ESE/Core/ResourceManager.hpp>
namespace ESE{
ResourceManager* ResourceManager::resourceManagerInstance = 0;

ResourceManager::ResourceManager(){
}

ResourceManager::~ResourceManager(){
}

TextureContainer* ResourceManager::getTextureContainer(){
	return &this->textureContainer;
}

ResourceManager* ResourceManager::instance(){
	if (resourceManagerInstance == 0) {
		resourceManagerInstance = new ResourceManager();
	}
	return resourceManagerInstance;
}

void ResourceManager::release(){
	if (resourceManagerInstance) {
		delete resourceManagerInstance;
	}
	resourceManagerInstance = 0;
}


}
