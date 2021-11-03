#include "Player.h"
#include "Animation.h"
#include <iostream>
#include <SFML/Window.hpp>
#define MAX_HP 3

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed):
	animation(texture, imageCount, switchTime, speed)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(60.0f, 60.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(600.0f, 500.0f);
	body.setTexture(texture);

	HP = 3;
	totalTime = 0;

	heartTexture.loadFromFile("pic/heart.png");
	for (int i = 0; i < HP; i++)
	{
		hearts.push_back(sf::Sprite(heartTexture));
		hearts[i].setPosition(sf::Vector2f(0 + (70 * i), 20));
		hearts[i].setScale(0.08, 0.08);
	}
}

Player::~Player()
{

}


void Player::LooseHP()
{
	HP -= 1;
}

void Player::GainHP()
{
	HP += 1;
	if (HP > MAX_HP)
	{
		HP = MAX_HP;
	}
}



void Player::Update(float deltatime,bool isSpeedBoost)
{

	velocity.x = 0.0f;
	velocity.y = 0.0f;

	totalTime += deltatime;

	if (isSpeedBoost)
	{
		speed = 500;
	}
	else
	{
		speed = 200;
	}


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


	if (velocity.x == 0.0f && velocity.y==0.0f)
	{
		row = 4;
	}



	if (deltatime != 0)
	{
		animation.Update(row, deltatime, faceRight);		
		body.setTextureRect(animation.uvRect);
	}
	
	
	body.move(velocity * deltatime);

}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::drawHeart(sf::RenderWindow& window)
{
	for (int i = 0; i < HP; i++)
	{
		window.draw(hearts[i]);
	}
}




