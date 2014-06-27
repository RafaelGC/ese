#include <ESE/Core/Entity.hpp>

namespace ESE{
	
	Entity::Entity(){
		
	}
	
	Entity::Entity(float x, float y, int width, int height){
		setPosition(x,y);
		setDimensions(width,height);
	}
	
	bool Entity::collidesWith(Entity entity){
		return rect.intersects(entity.getRect());
	}
	
	sf::FloatRect Entity::getRect(){
		return rect;
	}
	
	void Entity::setPosition(float x, float y){
		rect.top = y;
		rect.left = x;
	}
	
	void Entity::setDimensions(int w, int h){
		rect.width = w;
		rect.height = h;
	}
	
	sf::Vector2f Entity::getPosition(){
		return sf::Vector2f(rect.left,rect.top);
	}
	
	sf::Vector2i Entity::getDimensions(){
		return sf::Vector2i(rect.width,rect.height);
	}
}