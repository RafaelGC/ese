#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>

#include <ESE/Core/Log.hpp>
#include <ESE/Core/SceneManager.hpp>
#include <ESE/Core/ResourceManager.hpp>

namespace ESE
{
/**
 * @author Rafael González Carrizo
 * @brief Clase encargada de contener la ventana de la aplicación así como de instanciar y eliminar el gestor de recursos.
 * Un objeto de la clase Application debería ser el primero en ser instanciado al iniciar nuestro programa ya
 * que se encargará de iniciar los recursos. También deberá ser el último objeto en ser destruido porque el destructor
 * de esta clase libera los recursos (ResourceManager) así como las escenas (SceneManager).
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
	 * @brief Devuelve un puntero al gestor de escenas.
	 * */
	 virtual ESE::SceneManager *getSceneManager();
	/**
	 * @brief Este método llama al método manage() del SceneManager que es el bucle
	 * principal.
	 * */
	virtual void run();

};

}

#endif // APPLICATION_HPP
