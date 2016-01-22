#include <ESE/Core/SceneManager.hpp>

namespace ESE {

    //SceneManager* SceneManager::sceneManagerInstance = 0;

    SceneManager::SceneManager() {
    }

    SceneManager::~SceneManager() {
    }
    
    void SceneManager::setRenderWindow(sf::RenderWindow& renderWindow) {
        this->renderWindow = &renderWindow;
    }

    void SceneManager::addScene(ESE::Scene &scene, bool dontAddIfExists) {
        if (dontAddIfExists) {
            /*Si el usuario establece este argumento como true, se comprobará si existe una escena
             * ya añadida y, si existe, no se añadirá. Si se establece a false, no se comprobará y
             * será más eficiente.
             * Por defecto viene en false.
             */
            if (this->lookForScene(scene.getName())) {
                return;
            }
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
        ESE::Scene *scene;
        scene = lookForScene(name);
        if (scene) {
            scene->onActivate();
        }
    }

    void SceneManager::activateSceneAndDeactivateTheRest(std::string name) {
        for (auto it = scenes.begin(); it != scenes.end(); ++it) {
            if ((*it)->getName()!=name){
                (*it)->onDeactivate();
            }
        }
        activateScene(name);
    }

    void SceneManager::deactivateScene(std::string name) {
        ESE::Scene *scene = lookForScene(name);
        if (scene) {
            scene->onDeactivate();
        }
    }

    void SceneManager::pauseScene(std::string name) {
        ESE::Scene *scene = lookForScene(name);
        if (scene) {
            scene->onPause();
        }
    }
    
    void SceneManager::removeScene(std::string name) {
        deactivateScene(name);
        
        ESE::Scene* scene = lookForScene(name);
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
            
            (*it)->onDeactivate();
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
    
    bool SceneManager::allScenesInactive() const{
        for (auto it = scenes.begin(); it!=scenes.end(); ++it){
            if ((*it)->getState()!=ESE::Scene::State::INACTIVE){
                return false;
            }
        }
        return true;
    }

}

