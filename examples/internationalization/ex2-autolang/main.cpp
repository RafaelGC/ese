#include <Zelta/Core/Scene.hpp>
#include <Zelta/Core/SceneManager.hpp>
#include <Zelta/Core/FontManager.hpp>
#include <Zelta/Internationalization/Text.hpp>
#include <Zelta/Internationalization/TextContainer.hpp>
#include <Zelta/Internationalization/AutoLang.hpp>
#include <SFML/Graphics.hpp>

// CenteredText is a class that will keep a text
// horizontally centered on the screen.
// It inherits from zt::Text which, in turn,
// inherits from sf::Text.
class CenteredText : public zt::Text {
    public:
    // CenteredText needs the window width to calculate the
    // proper position for the text.
    CenteredText(float screenWidth) : screenWidth(screenWidth) {}
    
    // The translated() method is called by AutoLang when
    // the language is changed so that you can adapt the
    // zt::Text to the new content. In this case we want
    // the text to keep horizontally centered independently
    // of the language.
    // Note: translated() is inherited from zt::Text.
    void translated() {
        setPosition(
            screenWidth / 2 - getLocalBounds().width / 2, // Horizontal center.
            getPosition().y // Keep vertical position.
            );
    }
    
    private:
    float screenWidth;
};

class GameScene : public zt::Scene {
	public:
	GameScene(zt::SceneManager& sceneManager) :
	    zt::Scene("GameScene", sceneManager),
	    hello(getScreenSize().x),
	    bye(getScreenSize().x)
	    {
        
        // We are going to show some texts on the screen so we'll
        // need to load a font.
        fontManager.loadFromFile("sans", "FreeSans.ttf");
        
        hello.setFont(fontManager["sans"]);
        bye.setFont(fontManager["sans"]);
        
	    // Load the texts file.
	    // We can specify, through the second parameter,
	    // the language you want to load. If you don't
	    // specify it, all languages will be loaded.
	    // Take into account that you can use only loaded
	    // languages.
	    texts.load("text.lxml");
	    
	    // AutoLang uses the TextContainer to know
	    // what should be the content of the binded
	    // zt::Text.
	    autoLang.setTextSource(texts);
	    // Set the language.
	    autoLang.setLanguage(L"en");
	    
	    // We bind a zt::Text with a string in the zt::TextContainer
	    // through the AutoLang.
	    // This way, whenever we change the language of the AutoLang
	    // it will update all binded texts to the new language.
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
	
	CenteredText hello, bye;
	
	zt::TextContainer texts; // Contains the texts.
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

