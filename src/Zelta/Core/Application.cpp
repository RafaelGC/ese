#include <Zelta/Core/Application.hpp>

namespace zt {

    Application::Application() {

        sceneManager = &zt::SceneManager::instance();
        sceneManager->setRenderWindow(getWindow());

    }

    Application::~Application() {

    }

    sf::RenderWindow & Application::getWindow() {

        return window;
    }
    
    zt::SceneManager * Application::getSceneManager() {
        return this->sceneManager;
    }

    void Application::run() {
        zt::SceneManager::instance().manage();
    }

}

