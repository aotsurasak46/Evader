#pragma once
#include<SFML\Graphics.hpp>
#include "Collider.h"

class Bullet
{
	typedef void(*funcptr)();

public:
	
	Bullet(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Bullet();
	
	void fire(float x,float y);

	void Draw(sf::RenderWindow& window);
	
	sf::Vector2f getPos() { return bullet.getPosition(); }
	

	Collider GetCollider() { return Collider(bullet); }


private:

	sf::RectangleShape bullet;
};

