#include <ESE/Core/Application.hpp>

namespace ESE
{

Application::Application(){

	sceneManager = ESE::SceneManager::instance(getWindow());
	resourceManager = ESE::ResourceManager::instance();
	
}

Application::~Application(){
	
	ESE::SceneManager::release();
	ESE::ResourceManager::release();
	
}

sf::RenderWindow * Application::getWindow(){
	
	return &window;
}

ESE::ResourceManager* Application::getResourceManager(){
	return resourceManager;
}

void Application::run(){
	ESE::SceneManager::instance()->manage();
}

}

