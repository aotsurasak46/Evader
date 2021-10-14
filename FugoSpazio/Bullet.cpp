#include "Bullet.h"
#include "Player.h"
#include "Collider.h"

Bullet::Bullet(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	bullet.setTexture(texture);
	bullet.setSize(size);
	bullet.setPosition(position);
}

Bullet::~Bullet()
{

}

void Bullet::fire(float x,float y)
{
	bullet.move(x, y);
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(bullet);
}

