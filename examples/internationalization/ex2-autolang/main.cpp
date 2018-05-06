#include <Zelta/Core/Scene.hpp>
#include <Zelta/Core/SceneManager.hpp>
#include <Zelta/Core/FontManager.hpp>
#include <Zelta/Internationalization/Text.hpp>
#include <Zelta/Internationalization/AutoLang.hpp>
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
	    
	    autoLang.setTextSource(texts);
	    autoLang.setLanguage(L"en");
	    autoLang.bind(hello, L"greeting");
	    autoLang.bind(bye, L"bye");
    	
    	bye.setPosition(0, 50);
	}
	void manageEvents(float deltaTime, std::queue<sf::Event>& events) {

		sf::Event event;
		while (!events.empty()) {
			event = events.front();
			checkIfWindowClosed(event);
			
			if (event.type == sf::Event::KeyPressed) {
			    if (event.key.code == sf::Keyboard::E) {
			        autoLang.setLanguage(L"en");
			    }
			    
			    if (event.key.code == sf::Keyboard::S) {
			        autoLang.setLanguage(L"es");
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
	
	private:
	zt::FontManager fontManager;
	
	sf::Text hello, bye;
	
	zt::Text texts; // Contains the texts.
	zt::AutoLang autoLang;
};

int main() {
	sf::RenderWindow window;

	window.create(sf::VideoMode(800, 600), "ex-autolang");

	zt::SceneManager sceneManager(window);
	GameScene gameScene(sceneManager);

	sceneManager.addScene(gameScene);
	sceneManager.switchTo("GameScene");
	
	// The manage method contains the gameloop.
	sceneManager.manage();
	return 0;
}

