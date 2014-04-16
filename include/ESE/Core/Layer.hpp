#ifndef LAYER_HPP
#define LAYER_HPP

#include <SFML/Graphics/Drawable.hpp> // Base class: sf::Drawable
#include <SFML/Graphics/RenderTarget.hpp>

namespace ESE
{

class Layer : public sf::Drawable
{
	protected:
	bool visible;
	std::vector<sf::Drawable*>drawableItems;
public:
	Layer();
	virtual ~Layer();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void addDrawable(sf::Drawable*item);
	void setVisible(bool visible);

};

}

#endif // LAYER_HPP
