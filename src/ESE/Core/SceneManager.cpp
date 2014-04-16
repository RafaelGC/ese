#include <ESE/Core/SceneManager.hpp>

namespace ESE
{

SceneManager* SceneManager::sceneManagerInstance = 0;

SceneManager::SceneManager(sf::RenderWindow *window){
	this->window = window;
}

SceneManager::~SceneManager()
{
}

void SceneManager::addScene(std::string name, ESE::Scene* scene, bool dontAddIfExists){
	if (dontAddIfExists){
		/*Si el usuario establece este argumento como true, se comprobará si existe una escena
		 * ya añadida y, si existe, no se añadirá. Si se establece a false, no se comprobará y
		 * será más eficiente.
		 * Por defecto viene en false.
		 */
		 if (!this->lookForScene(name)){
			 return;
		 }
	}
	
	scenes.push_back(std::make_pair(name,scene));

}

void SceneManager::manage(){
	deltaTime.restart();
	
	bool thereIsAnActiveScene;
	/*En la variable booleana almacena si hay alguna escena activa, si no la hay, se termina con el bucle
	* porque no tiene sentido seguir manteniéndolo si no hay nada activo. No se le da ningún valor inicial
	* porque es lo primero que se hace al entrar en el bucle.
	* */
	while (true){
		thereIsAnActiveScene = false;
		/*Por defecto se le pone a false y, en el caso de que encontremos alguna escena activa (o en segundo plano)
		 * en el bucle que viene a continuación, la ponemos a true para que todo esto siga ejecutándose. En el momento
		 * en el que no haya ninguna escena activa, esta variable quedará con su valor por defecto: flase, y se terminará
		 * el bucle.
		 * */
		 
		 startRender();
		
		for (auto it = scenes.begin(); it!=scenes.end(); ++it){
			//Llamaremos al gameloop siempre que no esté la escena inactiva. Es decir, será llamado
			//cuando la escena esté en segundo plano o esté activa.
			
			ESE::Scene *scene = it->second;
			
			if (scene->getState()!=ESE::Scene::INACTIVE){
				//Si no está inactiva, llamamos a los métodos correspondientes.
				
				scene->gameloop(deltaTime.getElapsedTime().asSeconds());
				
				thereIsAnActiveScene = true;
				/*Ponemos la variable a true porque hemos encontrado una escena que no está inactiva,
				 * entonces tiene sentido seguir en la aplicación.
				 * */
			}
			
		}
		
		stopRender();
		
		if (!thereIsAnActiveScene){
			///Si no hay ninguna activa, salimos del bucle.
			break;
		}
	}
}

void SceneManager::startRender(){
	window->clear(sf::Color::Black);
}

void SceneManager::stopRender(){
	window->display();
}

void SceneManager::activateScene(std::string name){
	ESE::Scene *scene;
	scene = lookForScene(name);
	if (scene){scene->start();}
}
void SceneManager::activateSceneAndDeactivateTheRest(std::string name){
	for (auto it = scenes.begin();it!=scenes.end(); ++it){
		it->second->stop();
	}
	activateScene(name);
}
void SceneManager::deactivateScene(std::string name){
	ESE::Scene *scene = lookForScene(name);
	if (scene){scene->stop();}
}
void SceneManager::sentSceneToBackground(std::string name){
	ESE::Scene *scene = lookForScene(name);
	if (scene) {scene->pause();}
}

void SceneManager::deactivateAllScenes(){
	/*Pone en stop() todas la escenas, lo que conlleva a que el bucle de gestión acabe y la aplicación se cierre.
	 */
	for (auto it = scenes.begin(); it!=scenes.end(); ++it){
		ESE::Scene *scene = it->second;
		scene->stop();
	}
}

Scene* SceneManager::lookForScene(std::string name){
	/*La función busca si existe una escena con el nombre indicado, si existe devuelve el puntero,
	si no existe devuelve NULL.*/
	
	for (auto it = scenes.begin(); it!=scenes.end(); ++it){
		if (it->first == name){
			return it->second;
		}
	}
	ESE::Log::error("Scene not found.");
	return NULL;
}

SceneManager* SceneManager::instance(sf::RenderWindow *window){
	if (sceneManagerInstance == 0) {
		sceneManagerInstance = new SceneManager(window);
	}
	return sceneManagerInstance;
}

void SceneManager::release()
{
	if (sceneManagerInstance) {
		delete sceneManagerInstance;
	}
	sceneManagerInstance = 0;
}


}

