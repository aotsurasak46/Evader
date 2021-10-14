#include "Bullet.h"

Bullet::Bullet(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, Vector2f direction, float speed)
{
	bullet.setTexture(texture);
	bullet.setSize(size);
	bullet.setPosition(position);
	this->direction = direction;
	this->speed = speed;
}

Bullet::~Bullet()
{

}

void Bullet::fire(float x,float y)
{
	bullet.move(x, y);
}

void Bullet::Update(float deltaTime)
{
	bullet.move(direction * speed * deltaTime);
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(bullet);
}

