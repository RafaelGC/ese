#include <ESE/Core/Scene.hpp>

namespace ESE
{

Scene::Scene(sf::RenderWindow *window){
	setState(State::INACTIVE);
	setWindow(window);
}

Scene::~Scene(){
}

void Scene::setWindow(sf::RenderWindow *window){
	this->window = window;
}

Scene::State Scene::getState(){
	return state;
}

void Scene::setState(State state){
	this->state = state;
}

void Scene::start(){
	/*Lo primero que se hace antes de nada es comprobar que la escena no esté ya activada antes de
	 * activarla. No comprobar esto puede llevar a resultados inesperados. Lo mismo ocurre con los
	 * métodos stop() y pause.*/
	if (state!=State::ACTIVE){
		setState(State::ACTIVE);
	}
}

void Scene::stop(){
	if (state!=State::INACTIVE){
		setState(State::INACTIVE);
	}
}

void Scene::pause(){
	if (state!=State::BACKGROUND){
		setState(State::BACKGROUND);
	}
}

void Scene::gameloop(float deltaTime){
	if (state==State::ACTIVE){
		/*Sólo se llama a los métodos manageEvents() y logic() cuando la escena está activa, en caso
		 * se que el programador no desee este resultado, puede reimplementar este método en su clase.*/
		manageEvents();
		logic();
	}
	render();
	
}

void Scene::manageEvents(){
	while (window->pollEvent(events)){
		checkIfWindowClosed();
	}
}

void Scene::logic(){
	
}

void Scene::render(){
	/*Este es el método es heredado y reimplementado para hacer aparecer cosas en la ventana.
	 * Se libera al programador de la tarea de llamar a window->clear(...) y window->display()
	 * que es llamada automáticamente por el SceneManager en el momento apropiado. Si no se
	 * hiciese de esta manera y se llamase a los métodos mencionados desde el método render
	 * tendríamos problemas porque se actualizaría la pantalla más de una vez por iteración
	 * del bucle del SceneManager al haber más de una escena activa.*/
	 
}

void Scene::checkIfWindowClosed(){
	if (events.type==sf::Event::Closed){
		/*Si se ha presionado el botón de cerrar la ventana, llamamos a un método que desactiva
		 * todas las escenas, es decir, probablemente se acabe con la aplicación.*/
		ESE::SceneManager::instance()->deactivateAllScenes();
	}
}

}

