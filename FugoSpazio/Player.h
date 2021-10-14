#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include <time.h>
#include <iostream>
#include <Windows.h>
#include "Bullet.h"


class Player
{
public:

	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,float speed);
	~Player();

	void Update(float deltatime);
	void Draw(sf::RenderWindow& window);


	sf::Vector2f GetPosition() { return body.getPosition(); }

	Collider GetCollider() {  return Collider(body); }

private:

	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;

	sf::Vector2f velocity;
	float totalTime = 0.0f;
	float switchTime;
	

};

