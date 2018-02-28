#include <Zelta/Core/SceneManager.hpp>
#include <queue>

namespace zt {

    SceneManager::SceneManager(sf::RenderWindow& window) {
        this->renderWindow = &window;
    }

    SceneManager::~SceneManager() {
    }
    
    void SceneManager::setRenderWindow(sf::RenderWindow& renderWindow) {
        this->renderWindow = &renderWindow;
    }

    void SceneManager::addScene(zt::Scene &scene) {
        
        if (this->lookForScene(scene.getName())) {
            return;
        }

        scenes.push_back(&scene);        
    }
    
    void SceneManager::moveForward(const std::string& sceneName) {
        for (auto it = scenes.begin(); it != scenes.end(); ++it) {
            if ((*it)->getName() == sceneName && it != scenes.end()) {
                auto it2(it);
                std::swap((*it), *(++it2));
                break;
            }
        }
    }
    
    void SceneManager::moveToFront(const std::string& sceneName) {
        for (auto it = scenes.begin(); it != scenes.end(); ++it) {
            if ((*it)->getName() == sceneName) {
                std::swap((*it), *(--scenes.end()));
                break;
            }
        }
    }

    void SceneManager::moveBackward(const std::string& sceneName) {
        for (auto it = scenes.begin(); it != scenes.end(); ++it) {
            if ((*it)->getName() == sceneName && it != scenes.begin()) {
                auto it2(it);
                std::swap((*it), *(--it2));
                break;
            }
        }
    }
    
    void SceneManager::moveToBack(const std::string& sceneName) {
        for (auto it = scenes.begin(); it != scenes.end(); ++it) {
            if ((*it)->getName() == sceneName) {
                std::swap((*it), *(scenes.begin()));
                break;
            }
        }
    }

    void SceneManager::manage() {
        deltaTime.restart();
        sf::Event ev;
        
        while (!allScenesInactive()) {
            events.clear();
            while (renderWindow->pollEvent(ev)) {
                events.push_back(ev);
            }
            
            startRender();

            float dt = deltaTime.restart().asSeconds();

            for (auto it = scenes.begin(); it != scenes.end(); ++it) {
                (*it)->setEvents(std::queue<sf::Event>(events));
                (*it)->advanceTime(dt);

            }

            stopRender();
            
        }
    }

    void SceneManager::startRender() {
        renderWindow->clear(sf::Color::Black);
    }

    void SceneManager::stopRender() {
        renderWindow->display();
    }

    void SceneManager::activateScene(std::string name) {
        zt::Scene *scene;
        scene = lookForScene(name);
        if (scene && scene->getState() != Scene::State::ACTIVE) {
            scene->onActivate();
        }
    }

    void SceneManager::switchTo(std::string name) {
        for (auto it = scenes.begin(); it != scenes.end(); ++it) {
            if ((*it)->getName()!=name && (*it)->getState() != Scene::State::INACTIVE){
                (*it)->onDeactivate();
            }
        }
        activateScene(name);
    }

    void SceneManager::deactivateScene(std::string name) {
        zt::Scene *scene = lookForScene(name);
        if (scene && scene->getState() != Scene::State::INACTIVE) {
            scene->onDeactivate();
        }
    }

    void SceneManager::pauseScene(std::string name) {
        zt::Scene *scene = lookForScene(name);
        if (scene && scene->getState() != Scene::State::PAUSED) {
            scene->onPause();
        }
    }
    
    void SceneManager::removeScene(std::string name) {
        for (auto it = scenes.begin(); it != scenes.end(); ++it) {
            if ((*it)->getName() == name) {
                deactivateScene(name);
                scenes.erase(it);
                break;
            }
        }
    }

    void SceneManager::deactivateAllScenes() {
        /*Parar todas la escenas, lo que conlleva a que el bucle de gestión acabe y la aplicación se cierre.
         */
        for (auto it = scenes.begin(); it != scenes.end(); ++it) {
            if ((*it)->getState() != Scene::State::INACTIVE) {
                (*it)->onDeactivate();
            }
        }
    }

    Scene* SceneManager::lookForScene(std::string name) {
        /*La función busca si existe una escena con el nombre indicado, si existe devuelve el puntero,
        si no existe devuelve NULL.*/

        for (auto it = scenes.begin(); it != scenes.end(); ++it) {
            if ((*it)->getName() == name) {
                return (*it);
            }
        }
        return nullptr;
    }
    
    bool SceneManager::allScenesInactive() const {
        for (auto it = scenes.cbegin(); it!=scenes.cend(); ++it) {
            if ((*it)->getState() != Scene::State::INACTIVE) {
                return false;
            }
        }
        return true;
    }
    
    sf::RenderWindow& SceneManager::getRenderWindow() {
        return *renderWindow;
    }

}

