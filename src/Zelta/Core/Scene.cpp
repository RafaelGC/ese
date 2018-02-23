#include <Zelta/Core/Scene.hpp>

namespace zt {

    Scene::Scene(std::string name, SceneManager& sceneManager) {
        this->name = name;
        this->sceneManager = &sceneManager;
        this->window = &sceneManager.getRenderWindow();
        
        setState(State::INACTIVE);
        setWindow(sceneManager.getRenderWindow());
    }

    Scene::~Scene() {
    }

    void Scene::setWindow(sf::RenderWindow& window) {
        this->window = &window;
    }
    
    sf::RenderWindow& Scene::getWindow() {
        return *this->window;
    }
    
    sf::Vector2u Scene::getScreenSize() const {
        return this->window->getSize();
    }

    Scene::State Scene::getState() const{
        return state;
    }
    
    std::string Scene::getName() const{
        return name;
    }

    void Scene::setState(State state) {
        this->state = state;
    }

    void Scene::onActivate() {
        setState(State::ACTIVE);
    }

    void Scene::onDeactivate() {
        setState(State::INACTIVE);
    }

    void Scene::onPause() {
        setState(State::PAUSED);
    }
    
    bool Scene::isActive() const {
        return state == State::ACTIVE;
    }
    
    bool Scene::isInactive() const {
        return state == State::INACTIVE;
    }
    
    bool Scene::isPaused() const {
        return state == State::PAUSED;
    }

    void Scene::advanceTime(float deltaTime) {
        if (getState() == State::INACTIVE) {
            //Si la escena está inactiva, salimos directamente.
            return;
        }

        if (getState() == State::ACTIVE) {
            /*Sólo cuando la escena está activa llamamos a los métodos encargados
             de gestionar los eventos y la lógica del juego.*/
            manageEvents(deltaTime, this->events);
            logic(deltaTime);
        }

        //Por último, incluso cuando estamos en pausa, renderizamos.
        render();

    }

    void Scene::manageEvents(float deltaTime, std::queue<sf::Event>& events) {
        while (!events.empty()) {
            checkIfWindowClosed(events.front());
            
            events.pop();
        }
    }

    void Scene::checkIfWindowClosed(sf::Event event) {
        if (event.type == sf::Event::Closed) {
            /*Si se ha presionado el botón de cerrar la ventana, llamamos a un método que desactiva
             * todas las escenas, es decir, probablemente se acabe con la aplicación.*/
            sceneManager->deactivateAllScenes();
        }
    }

    void Scene::draw(const sf::Drawable &drawable) const {
        window->draw(drawable);
    }
    
    void Scene::clear(const sf::Color& color) {
        window->clear(color);
    }
    
    void Scene::setEvents(const std::queue<sf::Event>& events) {
        this->events = events;
    }

}
