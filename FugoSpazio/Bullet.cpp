#include "Bullet.h"

Bullet::Bullet( sf::Vector2f size, sf::Vector2f position, Vector2f direction, float speed)
{
	bullet.setFillColor(sf::Color::Green);
	bullet.setSize(size);
	bullet.setPosition(position);
	this->direction = direction;
	this->speed = speed;
}

Bullet::~Bullet()
{

}

void Bullet::Update(float deltaTime)
{
	bullet.move(direction * speed * deltaTime);
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(bullet);
}


