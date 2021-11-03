#pragma once
#include "AllHeader.h"
class Coffee
{
public:

	inline Coffee(sf::Texture& texture, sf::Vector2f position, sf::Vector2f size)
	{
		coffee.setTexture(texture);
		coffee.setPosition(position);
		coffee.setScale(size);
	}

	inline ~Coffee()
	{

	}

	inline void drawCoffee(sf::RenderWindow& window)
	{
		window.draw(coffee);
	}

	inline FloatRect getGlobalBounds() { return coffee.getGlobalBounds(); }

private:

	sf::Sprite coffee;

};

