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

    class SceneManager : public Singleton<SceneManager>{
        friend class Singleton;
    protected:
        /**
         * @brief Referencia a la ventana sobre la que se dibuja.
         * El SceneManager libera al programador de tener que llamar a los métodos window->clear()
         * y window->display() desde sus escenas. SceneManager se encarga de hacerlo las veces
         * necesarias, por eso necesita una referencia a la ventana.
         * */
        sf::RenderWindow *renderWindow;
        /*Imprescindible guardar una referencia a la ventana para llamar a los métodos de limpieza
         * y actualización tan sólo una vez por iteración del bucle de gestión. Si esas dos llamadas
         * se hicieran en el gameloop de la escena, estariamos actualizando  la ventana más de una vez
         * por cada interación en el caso de que haya más de una escena activa, algo que es absolutamente
         * innecesario.
         * */
        /**
         * @brief Se encarga de llamar a window->clear() antes de que ninguna escena renderice nada.
         */
        void startRender();
        /**
         * @brief Se encarga de llamar a window->display después de que todas las escenas hayan
         * renderizado lo suyo.
         * */
        void stopRender();

        /**
         * @brief Almacena un puntero a las escenas de las que se encarga el SceneManager.
         * Aquí es donde se guardan referencias a todas la escenas disponibles.
         * */
        std::list<zt::Scene*> scenes;

        /**
         * @brief Para contar los segundos que hay entre dos iteraciones del bucle de juego.
         * deltaTime es un cronómetro que nos permitirá calcular la diferencia de tiempo entre
         * dos iteraciones del bucle de juego. Es necesario para hacer que las aplicaciones se ejecuten
         * correctamente independientemente de la velocidad a la que se itera. Por comodidad, a la hora
         * de utilizar este cronómetro, se usará en segundos.
         * */
        sf::Clock deltaTime;

        /**
         * @param nombre Nombre de la escena.
         * @return Puntero a la escena, NULL si no existe tal escena.
         * */
        Scene* lookForScene(std::string name);
    public:
        
        /**
         * @param renderWindow Ventana donde se renderizarán las escenas.
         */
        void setRenderWindow(sf::RenderWindow & renderWindow);

        /**
         * @brief Añade una escena al vector, con el nombre que se le especifica.
         * @param scene Escena que se quiere añadir.
         * @param dontAddIfExists Si es <b>true</b>, antes de añadir la escena buscaremos si ya
         * hay alguna con ese nombre, si hay alguna con ese nombre, no la añadiremos. Si es <b>false</b> 
         * (valor por defecto), no se buscará y el programa será más eficiente.
         * */
        void addScene(zt::Scene&scene, bool dontAddIfExists = true);

        /**
         * @brief Bucle que termina cuando todas las escenas están <b>inactivas</b>.
         * */
        void manage();

        /**
         * @brief Activa la escena especificada en el nombre, si existe.
         * @param name Nombre de la escena.
         * */
        void activateScene(std::string name);
        /**
         * @brief Activa la escena especificada y desactiva todas las demás.
         * @param name Nombre de la escena.
         * */
        void switchTo(std::string name);

        /**
         * @brief Desactiva la escena especificada en el nombre, si existe.
         * @param name Nombre de la escena.
         * */
        void deactivateScene(std::string name);
        /**
         * @brief Desactiva todas las escenas y, por tanto, termina el bucle de manage(), lo que puede
         * causar el fin de la ejecución del programa.
         * */
        void deactivateAllScenes();

        /**
         * @brief Pausa la escena especificada en el nombre, si existe.
         * @param name Nombre de la escena.
         * */
        void pauseScene(std::string name);
        
        /**
         * @brief Elimina una escena.
         * 
         */
        void removeScene(std::string name);
        
        /**
         * @return True si TODAS las escenas están inactivas.
         */
        bool allScenesInactive() const;

    private:
        SceneManager();
        virtual ~SceneManager();

    };

}

#endif // SCENEMANAGER_HPP
