#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>

#include <ESE/Core/Config.hpp>
#include <ESE/Core/Log.hpp>
#include <ESE/Core/SceneManager.hpp>
#include <ESE/Core/ResourceManager.hpp>

namespace ESE
{
/**
 * @author Rafael González Carrizo
 * @brief Clase encargada de contener la ventana de la aplicación así como de instanciar y eliminar el gestor de recursos.
 * */
class Application
{
	protected:
	sf::RenderWindow window;
	ESE::SceneManager *sceneManager;
	ESE::ResourceManager *resourceManager;
	
public:
	Application();
	virtual ~Application();
	
	/**
	@return Devuelve un puntero de la ventana de la aplicación
	 */
	virtual sf::RenderWindow * getWindow();
	/**
	 * @return Devuelve un puntero del gestor de recursos.
	 * */
	virtual ESE::ResourceManager *getResourceManager();
	/**
	 * @brief Este método es un bucle encargado de gestionar las escenas.
	 * */
	virtual void run();

};

}

#endif // APPLICATION_HPP
