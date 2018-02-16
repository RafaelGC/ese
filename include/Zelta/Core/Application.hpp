#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>

#include <Zelta/Core/SceneManager.hpp>
#include <Zelta/Core/ResourceManager.hpp>
#include <Zelta/Core/Arguments.hpp>

namespace zt {

    /**
     * @brief This class is the main class of your program. It takes care of
     * initialise and release the resource manager.
     * Generally, this will be the first class to be instantiated and the last
     * one to be destroyed.
     */
    class Application {
    protected:
        sf::RenderWindow window;
        SceneManager *sceneManager;
        Arguments arguments;
        
    public:
        Application();
        Application(int argc, char** argv);
        virtual ~Application();

        /**
        @return Returns a reference to the application window.
         */
        virtual sf::RenderWindow & getWindow();
        
        /**
         * @brief Returns a pointer to the scene manager.
         * */
        virtual zt::SceneManager *getSceneManager();
        /**
         * @brief You'll call this method to start the app.
         * 
         * This method call the scene manager manage() method which is the
         * game loop.
         * */
        virtual void run();
        
        virtual const Arguments& getArguments() const;

    };

}

#endif // APPLICATION_HPP
