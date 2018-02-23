#include <Zelta/Core/Scene.hpp>
#include <Zelta/Core/SceneManager.hpp>
#include <SFML/Graphics.hpp>

class GameScene : public zt::Scene {
	public:
	// Note that zt::Scene constructor needs a scene name and a reference to
	// the scene manager.
	GameScene(zt::SceneManager& sceneManager) : zt::Scene("GameScene", sceneManager) {
		// Resource loading //
		appleTexture.loadFromFile("assets/apple.png");
		basketTexture.loadFromFile("assets/basket.png");
		
		basket.setTexture(basketTexture);
		basket.setScale(0.3, 0.3);
		basket.setPosition(0, 800 - 100/* - apple.getLocalBounds().height*/);
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

		// REAL TIME EVENT HANDLING //
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (basket.getPosition().x < getScreenSize().x - basket.getGlobalBounds().width) {
				basket.move(500 * deltaTime, 0);
			}
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (basket.getPosition().x > 0) {
				basket.move(-500 * deltaTime, 0);
			}
		}
	}

	void logic(float deltaTime) {
		// GAME LOGIC //
		
		// In the game logic we handle the generation of new
		// apples.
		if (generationClock.getElapsedTime().asSeconds() > 1.0f) {
			sf::Sprite newApple = sf::Sprite(appleTexture);
			float randX = rand() % (int)(getScreenSize().x - newApple.getGlobalBounds().width);
			newApple.setPosition(randX, -newApple.getGlobalBounds().height);
			newApple.setScale(0.2, 0.2);
			apples.push_back(newApple);
			
			generationClock.restart();
		}
		
		// We iterate through the apples...
		for (auto it = apples.begin(); it != apples.end();) {
			// ... and move it down.
			(*it).move(0, 400 * deltaTime);
			
			bool removeApple = false;
			
			// If the apple is outside de window we can destroy it.
			if ((*it).getPosition().y > getScreenSize().y) {
				removeApple = true;
			}
			
			// We should also check if the apple is touching the basket.
			// If so, we remove it.
			if (!removeApple && (*it).getGlobalBounds().intersects(basket.getGlobalBounds())) {
				removeApple = true;
			}
			
			if (removeApple) {
				it = apples.erase(it);
			}
			else {
				it++;
			}
		}
		
	}

	void render() {
		// DRAW HERE //
		
		clear(sf::Color(80, 120, 220));
		
		// draw() is a helper method from zt::Scene.
		for (sf::Sprite& apple : apples) {
			draw(apple);
		}
		draw(basket);
	}

	private:
	sf::Texture appleTexture,basketTexture;
	sf::Sprite basket;
	sf::Clock generationClock;
	
	std::list<sf::Sprite> apples;
};

int main() {
	sf::RenderWindow window;

	window.create(sf::VideoMode(600, 800), "ex1-game-v1");

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
