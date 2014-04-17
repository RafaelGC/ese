#include <ESE/Core/Scene.hpp>

namespace ESE
{

Scene::Scene(sf::RenderWindow *window)
{
	setState(State::INACTIVE);
	setWindow(window);
}

Scene::~Scene()
{
}

void Scene::setWindow(sf::RenderWindow *window)
{
	this->window = window;
}

Scene::State Scene::getState()
{
	return state;
}

void Scene::setState(State state)
{
	this->state = state;
}

void Scene::onActivate()
{
	setState(State::ACTIVE);
}

void Scene::onDeactivate()
{
	setState(State::INACTIVE);
}

void Scene::onPause()
{
	setState(State::PAUSED);
}

void Scene::gameloop(float deltaTime)
{
	if (getState()==INACTIVE) {
		//Si la escena está inactiva, salimos directamente.
		return;
	}

	if (getState()==ACTIVE) {
		/*Sólo cuando la escena está activa llamamos a los métodos encargados
		 de gestionar los eventos y la lógica del juego.*/
		manageEvents(deltaTime);
		logic(deltaTime);
	}

	//Por último, incluso cuando estamos en pausa, renderizamos.
	render();

}

void Scene::manageEvents(float deltaTime)
{
	while (window->pollEvent(events)) {
		checkIfWindowClosed();
	}
}

void Scene::checkIfWindowClosed()
{
	if (events.type==sf::Event::Closed) {
		/*Si se ha presionado el botón de cerrar la ventana, llamamos a un método que desactiva
		 * todas las escenas, es decir, probablemente se acabe con la aplicación.*/
		ESE::SceneManager::instance()->deactivateAllScenes();
	}
}

void Scene::draw(sf::Drawable &drawable){
	window->draw(drawable);
}

}
