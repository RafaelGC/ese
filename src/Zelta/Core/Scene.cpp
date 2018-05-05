#include <Zelta/Core/Scene.hpp>

namespace zt {

    Scene::Scene(std::string name, SceneManager& sceneManager) {
        this->name = name;
        this->sceneManager = &sceneManager;
        this->window = &sceneManager.getRenderWindow();
        
        this->state = State::INACTIVE;
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
    
    zt::NestableClock& Scene::getMasterClock() {
        return this->masterClock;
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
        masterClock.resume();
    }

    void Scene::onDeactivate() {
        setState(State::INACTIVE);
        masterClock.pause();
    }

    void Scene::onPause() {
        setState(State::PAUSED);
        masterClock.pause();
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
    
    SceneManager& Scene::getSceneManager() {
        return *this->sceneManager;
    }

    void Scene::advanceTime(float deltaTime) {
        // The gameloop (which is in the SceneManager) will call the
        // advanceTime() method of all the scenes.
        // From the advanceTime() method we'll call the manageEvents(), logic()
        // and render() methods.
        
        // If the scene is INACTIVE we don't really want any of those methods
        // to be called.
        if (getState() == State::INACTIVE) {
            return;
        }

        if (getState() == State::ACTIVE) {
            // Only when the scene is ACTIVE we will call manageEvents() and logic().
            manageEvents(deltaTime, this->events);
            logic(deltaTime);
        }

        // Finally, we'll call render(). Note that this method will be called
        // even when the scene is paused.
        render();
        
        // If you want to change the behaviour of the states, you can override
        // this method.

    }

    void Scene::manageEvents(float deltaTime, std::queue<sf::Event>& events) {
        // The default implementation of manageEvents() just iterates over
        // the event queue and check if the user want to close the application.
        while (!events.empty()) {
            checkIfWindowClosed(events.front());
            
            events.pop();
        }
    }

    void Scene::checkIfWindowClosed(sf::Event event) {
        if (event.type == sf::Event::Closed) {
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
