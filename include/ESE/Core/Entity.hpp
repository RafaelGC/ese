#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace ESE{
	class Entity{
	protected:
		/**
		 * @brief Contiene la posición (top para la y y left para la x), así como sus dimensiones
		 * (width, height).
		 * */
		sf::FloatRect rect;
		
	public:
		Entity();
		Entity(float x, float y, int width, int height);
		
		bool collidesWith(Entity entity);
		sf::FloatRect getRect();
		
		void setPosition(float x, float y);
		void setDimensions(int w, int h);
		
		sf::Vector2f getPosition();
		sf::Vector2i getDimensions();
	};

}
#endif