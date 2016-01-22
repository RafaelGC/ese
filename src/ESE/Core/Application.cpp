#include <ESE/Core/Application.hpp>

namespace ESE {

    Application::Application() {

        sceneManager = &ESE::SceneManager::instance();
        sceneManager->setRenderWindow(getWindow());
        resourceManager = ESE::ResourceManager::instance();

    }

    Application::~Application() {
        ESE::ResourceManager::release();

    }

    sf::RenderWindow & Application::getWindow() {

        return window;
    }

    ESE::ResourceManager* Application::getResourceManager() {
        return resourceManager;
    }

    ESE::SceneManager * Application::getSceneManager() {
        return this->sceneManager;
    }

    void Application::run() {
        ESE::SceneManager::instance().manage();
    }

}

