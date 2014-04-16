#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <string>
#include <vector>

#include <SFML/System.hpp>

#include <ESE/Core/Scene.hpp>
#include <ESE/Core/Log.hpp>

namespace ESE
{
class Scene;
//Forward declaration.
class SceneManager
{
protected:
	static SceneManager* sceneManagerInstance;
	
	sf::RenderWindow *window;
	/*Imprescindible guardar una referencia a la ventana para llamar a los métodos de limpieza
	 * y actualización tan sólo una vez por iteración del bucle de gestión. Si esas dos llamadas
	 * se hicieran en el gameloop de la escena, estariamos actualizando  la ventana más de una vez
	 * por cada interación en el caso de que haya más de una escena activa, algo que es absolutamente
	 * innecesario.
	 * */
	 void startRender();
	 void stopRender();
	 /*Los dos métodos anteriores se encargan, respectivamente, de limpiar la ventana y de actualarla,
	  * es decir, son los métodos que se dedican a trabajar con window.*/
	
	std::vector<std::pair<std::string,ESE::Scene*>> scenes;
	
	/*Aquí es donde se guardan referencias a todas la escenas disponibles. Cada escena está
	 * relacionada con un string, que es su nombre.
	 * He optado por dos vectores en vez de por un std::map porque debería ser más rápido
	 * iterar en un vector que en un map.
	 * Fuente: http://stackoverflow.com/questions/730498/iterator-access-performance-for-stl-map-vs-vector
	 * Podría ser interesante hacer un vector de pares.
	 * */
	 
	 sf::Clock deltaTime;
	 /*deltaTime es un cronómetro que nos permitirá calcular la diferencia de tiempo entre
	  * dos iteraciones del bucle de juego. Es necesario para hacer que las aplicaciones se ejecuten
	  * correctamente independientemente de la velocidad a la que se itera. Por comodidad, a la hora
	  * de utilizar este cronómetro, se usará en segundos.
	  */
	  
	  Scene* lookForScene(std::string nombre);
public:
	static SceneManager* instance(sf::RenderWindow *window=NULL);
	static void release();
	
	void addScene(std::string name, ESE::Scene*scene, bool dontAddIfExists=false);
	void manage();
	
	void activateScene(std::string name);
	void activateSceneAndDeactivateTheRest(std::string name);
	
	void deactivateScene(std::string name);
	void deactivateAllScenes();
	
	void sentSceneToBackground(std::string name);
	
private:
	SceneManager(sf::RenderWindow *window);
	virtual ~SceneManager();

};

}

#endif // SCENEMANAGER_HPP
