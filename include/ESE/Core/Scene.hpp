#ifndef SCENE_HPP
#define SCENE_HPP

#include <map>

#include <SFML/Graphics.hpp>

#include <ESE/Core/Config.hpp>
#include <ESE/Core/Log.hpp>
#include <ESE/Core/SceneManager.hpp>

namespace ESE
{
	
class SceneManager;
//Forward declaration
class Scene
{
	friend class SceneManager;
	
	public:
	enum State{ACTIVE, BACKGROUND, INACTIVE};
	
		/**
	 * @brief Construye una escena <b>inactiva</b>.
	 * @param window Referencia a la ventana donde se dibujarán los elementos de la escena.
	 * */
	Scene(sf::RenderWindow*window);
	virtual ~Scene();
		/**
	 * @return Estado actual de la escena.
	 * */
	virtual State getState();
		/**
	 * @brief Permite seleccionar la ventana sobre la que se dibujará la escena.
	 * @param window Ventana objetivo.
	 * */
	virtual void setWindow(sf::RenderWindow*window);
	
	protected:
		/**
	 * @brief Estado actual.
	 * */
	State state;
	/**
	 * @brief Referencia a la ventana sobre la que se dibujará la escena.
	 * */
	sf::RenderWindow *window;
	sf::Event events;
	
	/**
	 * @brief Activa la escena si no lo está.
	 * */
	virtual void start();
	/**
	 * @brief Para la escena (estado INACTIVE) si no lo está.
	 * */
	virtual void stop();
	/**
	 * @brief Pausa la escena si no lo está (el estado será BACKGROUND)..
	 * */
	virtual void pause();
	/**
	 * @brief Cambia el estado actual.
	 * @param state Nuevo estado.
	 * */
	virtual void setState(State state);
	
	/**
	 * @brief Se encarga de llamar a los métodos manageEvents(), logic() y render(). El programador
	 * <b>NO</b> llama a este método, de eso se encarga el SceneManager.
	 * @param deltaTime Segundos que han transcurrido desde la última vez que llamamos
	 * a esta función. Se e
	 * Este método <b>no es un bucle</b>, sino que está hecho para ser llamado desde
	 * un bucle (el verdadero bucle de juego), que está en el método manageEvents() del
	 * gestor de estados, que a su vez debería ser llamado por el método run() de Application.
	 * <br><br>
	 * Los métodos manageEvents() y logic() <b>sólo son llamados</b> si la escena está activa.El
	 * método render() es llamado también cuando está en pausa.
	 * <br>Si la escena está inactiva, el SceneManager se encarga de <b>no</b> llamar a ninguno
	 * de los tres métodos.
	 * <br><br>
	 * Si el programador quiere <b>otro comportamiento</b>, puede reimplementar este método a su gusto.
	 * */
	virtual void gameloop(float deltaTime);
	/**
	 * @brief Método pensado para ser reimplementado. Aquí iría todo lo relacionado con la gestión de eventos.
	 * */
	virtual void manageEvents();
	/**
	 * @brief Lógica del juego (IA, colisiones, etc).
	 * */
	virtual void logic();
	/**
	 * @brief En ella se dibujará lo que sea necesario.
	 * */
	virtual void render();
	
	/**
	 * @brief Un método rápido para finalizar la escena si el botón de cerrar ha sido pulsado.
	 * Se debe utilizar dentro manageEvents(), dentro del bucle que analiza sf::Events.
	 * */
	virtual void checkIfWindowClosed();
};

}

#endif // SCENE_HPP
