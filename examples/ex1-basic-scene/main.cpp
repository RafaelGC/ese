#include <Zelta/Core/Scene.hpp>
#include <Zelta/Core/SceneManager.hpp>
#include <SFML/Graphics.hpp>

class GameScene : public zt::Scene {
	public:
	// Note that zt::Scene constructor needs a scene name and a reference to
	// the scene manager.
	GameScene(zt::SceneManager& sceneManager) : zt::Scene("GameScene", sceneManager) {
	}
	void manageEvents(float deltaTime, std::queue<sf::Event>& events) {
		// EVENT HANDLING METHOD //

		sf::Event event;
		while (!events.empty()) { // While there are events to handle...
			// We get the  first event in the queue.
			event = events.front();

			// This is a helper function that will check if the
			// user has closed the window. If so, the game
			// will close.
			checkIfWindowClosed(event);

			// HERE YOU CAN HANDLE MORE EVENTS //

			events.pop();
		}


	}

	void logic(float deltaTime) {
		// GAME LOGIC //
	}

	void render() {
		// DRAW HERE //
	}

	private:
};

int main() {
	sf::RenderWindow window;

	window.create(sf::VideoMode(800, 600), "ex1-game-v1");

	zt::SceneManager sceneManager(window);
	GameScene gameScene(sceneManager);

	sceneManager.addScene(gameScene);
	// switchTo() activates the scene especified
	// and deactivates the others.
	sceneManager.switchTo("GameScene");
	
	// The manage method contains the gameloop.
	sceneManager.manage();
	return 0;
}
