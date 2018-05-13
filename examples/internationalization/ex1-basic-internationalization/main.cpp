#include <Zelta/Core/Scene.hpp>
#include <Zelta/Core/SceneManager.hpp>
#include <Zelta/Core/FontManager.hpp>
#include <Zelta/Internationalization/TextContainer.hpp>
#include <SFML/Graphics.hpp>

class GameScene : public zt::Scene {
	public:
	GameScene(zt::SceneManager& sceneManager) : zt::Scene("GameScene", sceneManager) {
        
        // We are going to show some texts on the screen so we'll
        // need to load a font.
        fontManager.loadFromFile("sans", "FreeSans.ttf");
        
        hello.setFont(fontManager["sans"]);
        bye.setFont(fontManager["sans"]);
        
	    // Load the texts file.
	    texts.load("text.lxml");
	    
	    // Set the English version.
    	texts.in(L"en");
    	
        updateStrings();
    	
    	
    	bye.setPosition(0, 50);
	}
	void manageEvents(float deltaTime, std::queue<sf::Event>& events) {

		sf::Event event;
		while (!events.empty()) {
			event = events.front();
			checkIfWindowClosed(event);
			
			if (event.type == sf::Event::KeyPressed) {
			    if (event.key.code == sf::Keyboard::E) {
			        texts.in(L"en");
			        updateStrings();
			    }
			    
			    if (event.key.code == sf::Keyboard::S) {
			        texts.in(L"es");
			        updateStrings();
			    }
			}
			
			events.pop();
		}


	}

	void logic(float deltaTime) {
	}

	void render() {
	    draw(hello);
	    draw(bye);
	}
	
	void updateStrings() {
	    hello.setString(texts.get(L"greeting"));
    	bye.setString(texts.get(L"bye"));
	}

	private:
	zt::FontManager fontManager;
	
	sf::Text hello, bye;
	
	zt::TextContainer texts; // Contains the texts.
};

int main() {
	sf::RenderWindow window;

	window.create(sf::VideoMode(800, 600), "ex-basic-internationalization");

	zt::SceneManager sceneManager(window);
	GameScene gameScene(sceneManager);

	sceneManager.addScene(gameScene);
	sceneManager.switchTo("GameScene");
	
	// The manage method contains the gameloop.
	sceneManager.manage();
	return 0;
}

