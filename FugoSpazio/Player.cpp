#include "Player.h"
#include "Animation.h"
#include <iostream>
#include <SFML/Window.hpp>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed):
	animation(texture, imageCount, switchTime, speed)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(80.0f, 80.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(600.0f, 500.0f);
	body.setTexture(texture);
}

Player::~Player()
{
}


void Player::Update(float deltatime)
{
	
	velocity.x = 0.0f;
	velocity.y = 0.0f;

	totalTime += deltatime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
	{
		row = 3;
		velocity.x -= speed ;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
	{
		row = 1;
		velocity.x += speed ;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) )
	{
		row = 2;
		velocity.y -= speed ;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) )
	{
		row = 0;
		velocity.y += speed ;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			velocity.x *= 3;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			velocity.x *= 3;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			velocity.y *= 3;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			velocity.y *= 3;

		}		
		
	}

	if (velocity.x == 0.0f && velocity.y==0.0f)
	{
		row = 4;
	}

	animation.Update(row, deltatime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltatime);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}


