#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <string>
#include <vector>
#include <list>

#include <SFML/System.hpp>

#include <Zelta/Core/Singleton.hpp>
#include <Zelta/Core/Scene.hpp>

#include <iostream>

namespace zt {
    class Scene;
    //Forward declaration.

    /**
     * @brief This class manages scenes. Scenes added to the scene manager must
     * have a unique name. You'll activate them through the SceneManager.
     * 
     * The manage() method contains the main loop which will call the
     * manageEvents(), logic() and render() methods of your scenes.
     */
    class SceneManager {
    public:
        SceneManager(sf::RenderWindow& window);
        virtual ~SceneManager();
        
        /**
         * @brief Sets the window.
         * @param renderWindow Window
         */
        void setRenderWindow(sf::RenderWindow & renderWindow);

        /**
         * @brief Adds a Scene.
         * @param scene Scene.
         * */
        void addScene(zt::Scene& scene);

        /**
         * @brief This is the actual game loop. This function will return when
         * all scenes are inactive.
         * */
        void manage();

        /**
         * @brief Activates a Scene.
         * @param name Name of the scene.
         * */
        void activateScene(std::string name);
        /**
         * @brief Activate a scene and deactivate the others.
         * @param name Name of the scene that will be activated.
         * */
        void switchTo(std::string name);

        /**
         * @brief Deactivate a scene.
         * @param name Name of the scene.
         * */
        void deactivateScene(std::string name);
        
        /**
         * @brief Deactivates all scenes, thus, the game loop will finish.
         * */
        void deactivateAllScenes();

        /**
         * @brief Pauses the scene.
         * @param name Name of the scene.
         * */
        void pauseScene(std::string name);
        
        /**
         * @brief Removes a scene.
         */
        void removeScene(std::string name);
        
        /**
         * @return Returns true if all scenes are inactive.
         */
        bool allScenesInactive() const;

        sf::RenderWindow& getRenderWindow();
    protected:
        /**
         * @brief Pointer to the window.
         * The SceneManager frees you from having to call window->clear() and
         * window->display() from your scenes.
         * */
        sf::RenderWindow *renderWindow;

        /**
         * @brief This method is called just before the all render() methods from
         * scenes are called. It clears the screen.
         */
        void startRender();
        /**
         * @brief This method is called just after all render() methods from scenes
         * are called. It displays the drawed stuff.
         * */
        void stopRender();

        std::list<zt::Scene*> scenes;

        /**
         * @brief This clock is used to calc the delta time. All scenes get this information
         * from the SceneManager and use that number to move things accordingly with it.
         */
        sf::Clock deltaTime;

        /**
         * Returns a Scene by its name.
         * @param nombre Scene name.
         * @return Pointer to the scene or nullptr if it does not exist.
         * */
        Scene* lookForScene(std::string name);

    };

}

#endif // SCENEMANAGER_HPP
