#ifndef LAYER_HPP
#define LAYER_HPP

#include <SFML/Graphics/Drawable.hpp> // Base class: sf::Drawable
#include <SFML/Graphics/RenderTarget.hpp>

namespace ESE
{
/**
 * @brief Contenedor de objetos dibujables.
 * Esta clase permite agrupar ciertos elementos dibujables (sprites, textos, etc) para poder
 * hacerlos desaparecer al mismo tiempo.
 * */
class Layer : public sf::Drawable
{
	protected:
	/**
	 * @brief Sólo cuanto es true se dibujarán los elementos de la capa.
	 * */
	bool visible;
	/**
	 * @brief Vector que contiene un puntero a los dibujables de esta capa.
	 * */
	std::vector<sf::Drawable*>drawableItems;
	public:
	/**
	 * @brief El constructor pone <b>visible = true</b>
	 * */
	Layer();
	virtual ~Layer();
	/**
	 * @brief Método heredado que se encarga de dibujar todos los elementos de la capa
	 * si esta está visible.
	 * */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	/**
	 * @brief Añade un elemento dibujable a la capa.
	 * */
	void addDrawable(sf::Drawable*item);
	/**
	 * @brief Permite alternar la capa entre visible e invisible.
	 * */
	void setVisible(bool visible);

};

}

#endif // LAYER_HPP
