#pragma once
#include "AllHeader.h"
#include "Collider.h"
#include "Player.h"

class Bullet
{
	typedef void(*funcptr)();
private:
	sf::RectangleShape bullet;
	Vector2f direction;
	float speed;

public:
	
	Bullet(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, Vector2f direction, float speed);
	~Bullet();
	
	void fire(float x,float y);

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	
	inline sf::Vector2f getPos() { return bullet.getPosition(); }
	FloatRect getGlobalBounds() { return bullet.getGlobalBounds(); }
	inline Collider GetCollider() { return Collider(bullet); }
	inline bool isOutOfScreen()
	{
		if (direction == Vector2f(1, 0))
		{
			return bullet.getPosition().x > 1000;
		}
		else if (direction == Vector2f(-1, 0))
		{
			return bullet.getPosition().x + bullet.getSize().x < 0;
		}
		else if (direction == Vector2f(0, 1))
		{
			return bullet.getPosition().y > 1000;
		}
		else if (direction == Vector2f(0, -1))
		{
			return bullet.getPosition().y + bullet.getSize().y < 0;
		}
		return false;
	}
};

