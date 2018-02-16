#ifndef ZELTALIB_SCENE_HPP
#define ZELTALIB_SCENE_HPP

#include <map>

#include <SFML/Graphics.hpp>

#include <Zelta/Core/SceneManager.hpp>
#include <Zelta/Core/Animatable.hpp>

namespace zt {

    class SceneManager;
    //Forward declaration
    /**
     * @brief Represents a game scene. It could be the main menu, the credits scene, etc.
     * This class is made to be inherited from it. Scenes must have a unique name.
     * 
     * There are three methods you'll want/have to override:
     * -manageEvents(): this is the place to manage the events. The current behaviour
     * of this method is to finish the game when you click the X button.
     * -logic(): you can place the logic here.
     * -draw(): rendering stuff goes here.
     * 
     * The Scene class does not really care about where you put your logic or your
     * event handling. That means that you can put your logic in the manageEvents()
     * method and handle the events in the logic() one. Of course, you shouldn't.
     * 
     * 
     * Both manageEvents() and logic() receive the deltaTime as argument to move 
     * things accordingly with the frame rate, render() doesn't because you should
     * not update anything there.
     * 
     * Sometimes the order in which these methods are called is important. By default,
     * they are called like this: manageEvents() then logic() then render().
     * You can change this behaviour by overriding the advanceTime() method.
     * 
     * Keep in mind that the advanceTime() method is called from the game loop, but
     * this method <b>is not</b> the game loop. The game loop is in the scene manager.
     */
    class Scene : public Animatable{
        friend class SceneManager;

    public:

        /**
         * @brief States of a scene.
         * */
        enum class State {
            ACTIVE, PAUSED, INACTIVE
        };

        /**
         * @brief Constructs an <b>inactive</b> scene.
         * @param name Unique name for the scene.
         * @param window Reference to the window where you'll draw your stuff.
         * */
        Scene(std::string name, sf::RenderWindow& window);
        virtual ~Scene();
        /**
         * @return Current state. @see State
         * */
        State getState() const;
        
        std::string getName() const;
        
        /**
         * @brief Allows you to change the window where you'll be drawing.
         * @param window Window.
         * */
        virtual void setWindow(sf::RenderWindow& window);
        
        virtual sf::RenderWindow& getWindow();

    protected:
        /**
         * @brief Current state.
         * */
        State state;
        /**
         * @brief Pointer to the current window.
         * */
        sf::RenderWindow *window;
        sf::Event events;
        std::string name;

        /**
         * @brief This method gets called when the scene is activated.
         * @note If you override this method do not forget to call the
         * parent onActivate() method or it will not be activated.
         * */
        virtual void onActivate();
        
        /**
         * @brief This method gets called when the scene is deactivated.
         * @note If you override this method do not forget to call the
         * parent onDeactivated() method or it will not be activated.
         * */
        virtual void onDeactivate();
        
        /**
         * @brief This method gets called when the scene is paused.
         * @note If you override this method do not forget to call the
         * parent onPaused() method or it will not be activated.
         * */
        virtual void onPause();
        
        virtual bool isActive() const;
        virtual bool isInactive() const;
        virtual bool isPaused() const;
        
        /**
         * @brief Changes the state of the scene. It's not public because
         * you should change the state of the scene through the scene manager.
         * @param state New state.
         * */
        virtual void setState(State state);

        /**
         * @brief This method calls the manageEvents(), logic() and render() methods. You don't call
         * this method, it's called by the scene manager.
         * 
         * By default, manageEvents() and logic() are only called when the scene is active. The
         * render() method is also called when the scene is paused. You may want to
         * override this behaviour.
         * @param deltaTime
         */
        virtual void advanceTime(float deltaTime);
        
        /**
         * @brief You should override this method and handle the events from here.
         * */
        virtual void manageEvents(float deltaTime);
        
        /**
         * @brief You must implement this method. You should handle the logic here.
         * */
        virtual void logic(float deltaTime) = 0;
        
        /**
         * @brief The drawing stuff goes here. Note that you don't need to call
         * window->clear() nor window->display(). The scene manager cares about
         * that. 
         * */
        virtual void render() = 0;

        /**
         * @brief If you call this method inside the poll event loop it will stop
         * all scenes when the window X button is pressed.
         * */
        virtual void checkIfWindowClosed();

        /**
         * @brief Helper method to draw things easily. Instead of calling window->draw(something)
         * you just need to call draw(something).
         * */
        virtual void draw(const sf::Drawable &drawable) const;
    };

}

#endif // SCENE_HPP
