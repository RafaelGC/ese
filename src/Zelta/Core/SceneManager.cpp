#include <Zelta/Core/SceneManager.hpp>

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

    void SceneManager::manage() {
        deltaTime.restart();

        while (!allScenesInactive()) {
            startRender();

            float dt = deltaTime.restart().asSeconds();

            for (auto it = scenes.begin(); it != scenes.end(); ++it) {
                
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
        deactivateScene(name);
        
        zt::Scene* scene = lookForScene(name);
        for (auto it = scenes.begin(); it!=scenes.end(); ++it) {
            if ((*it)==scene) {
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
                return *it;
            }
        }
        return nullptr;
    }
    
    bool SceneManager::allScenesInactive() const {
        for (auto it = scenes.begin(); it!=scenes.end(); ++it){
            if ((*it)->getState() != zt::Scene::State::INACTIVE){
                return false;
            }
        }
        return true;
    }
    
    sf::RenderWindow& SceneManager::getRenderWindow() {
        return *renderWindow;
    }

}

