#include <Zelta/Core/Application.hpp>

namespace zt {

    Application::Application() {
        sceneManager = &zt::SceneManager::instance();
        sceneManager->setRenderWindow(getWindow());
    }
    
    Application::Application(int argc, char** argv) : Application() {
        arguments.initialize(argc, argv);
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
    
    const Arguments& Application::getArguments() const {
        return arguments;
    }

}

