#include <ESE/Core/SceneManager.hpp>

namespace ESE {

    SceneManager* SceneManager::sceneManagerInstance = 0;

    SceneManager::SceneManager(sf::RenderWindow *window) {
        this->window = window;
    }

    SceneManager::~SceneManager() {
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

        bool canIFinishTheLoop;
        /*Esta variable booleana comienza valiendo true (es decir, suponemos que no hay ninguna escena
         * activa), pero en el momento en el que encontramos una escena activa o pausada lo ponemos a
         * false. Si cuando hemos revisado todas las escenas esta variable sigue a true significa que todas
         * las escenas están vacías y, por tanto, podemos terminar con la ejecución del programa.*/

        while (true) {
            canIFinishTheLoop = true;

            startRender();

            float dt = deltaTime.restart().asSeconds();

            for (auto it = scenes.begin(); it != scenes.end(); ++it) {
                //Llamaremos al gameloop siempre que no esté la escena inactiva. Es decir, será llamado
                //cuando la escena esté en segundo plano o esté activa.

                (*it)->advanceTime(dt);

                if ((*it)->getState() != ESE::Scene::INACTIVE) {
                    canIFinishTheLoop = false;
                }

            }

            stopRender();

            if (canIFinishTheLoop) {
                ///Si no hay ninguna activa, salimos del bucle.
                break;
            }
        }
    }

    void SceneManager::startRender() {
        window->clear(sf::Color::Black);
    }

    void SceneManager::stopRender() {
        window->display();
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
            (*it)->onDeactivate();
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
            std::cout << (*it)->getName() << ", " << name << std::endl;
            if ((*it)->getName() == name) {
                return *it;
            }
        }
        return nullptr;
    }

    SceneManager* SceneManager::instance(sf::RenderWindow *window) {
        if (sceneManagerInstance == nullptr) {
            sceneManagerInstance = new SceneManager(window);
        }
        return sceneManagerInstance;
    }

    void SceneManager::release() {
        if (sceneManagerInstance) {
            delete sceneManagerInstance;
        }
        sceneManagerInstance = nullptr;
    }


}

