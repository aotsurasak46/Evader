#pragma once
#include "AllHeader.h"
class Heart
{

public:

	inline Heart(sf::Texture &texture, sf::Vector2f position, sf::Vector2f size)
	{
		heartItem.setTexture(texture);
		heartItem.setPosition(position);
		heartItem.setScale(size);
	}

	inline ~Heart()
	{

	}

	inline void drawHeart(sf::RenderWindow& window)
	{
		window.draw(heartItem);
	}

	inline FloatRect getGlobalBounds() { return heartItem.getGlobalBounds(); }

private:
	sf::Sprite heartItem;

};

