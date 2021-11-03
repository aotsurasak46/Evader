#pragma once
#include "AllHeader.h"
class Coin
{
public:

	inline Coin(sf::Texture& texture, sf::Vector2f position, sf::Vector2f size)
	{
		coin.setTexture(texture);
		coin.setPosition(position);
		coin.setScale(size);
	}

	inline ~Coin()
	{

	}

	inline void drawCoin(sf::RenderWindow& window)
	{
		window.draw(coin);
	}

	inline FloatRect getGlobalBounds() { return coin.getGlobalBounds(); }

private:
	sf::Sprite coin;
};

