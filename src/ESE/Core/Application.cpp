#include <ESE/Core/Application.hpp>

namespace ESE {

    Application::Application() {

        sceneManager = &ESE::SceneManager::instance();
        sceneManager->setRenderWindow(getWindow());

    }

    Application::~Application() {

    }

    sf::RenderWindow & Application::getWindow() {

        return window;
    }
    
    ESE::SceneManager * Application::getSceneManager() {
        return this->sceneManager;
    }

    void Application::run() {
        ESE::SceneManager::instance().manage();
    }

}

