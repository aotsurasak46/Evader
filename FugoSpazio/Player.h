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

	void LooseHP();
	void GainHP();
	inline int getHP() { return HP; }

	void Update(float deltatime, bool isSpeedBoost);
	void Draw(sf::RenderWindow& window);

	void drawHeart(sf::RenderWindow& window);
	void drawDead(sf::RenderWindow& window);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	FloatRect getGlobalBounds() { return body.getGlobalBounds(); }
	Collider GetCollider() {  return Collider(body); }

private:

	sf::RectangleShape body;
	
	std::vector<sf::Sprite> hearts;

	sf::Texture heartTexture;
	sf::Texture playerDeadTexture;

	Animation animation;
	unsigned int row;
	float speed ;
	bool faceRight;

	int HP ;
	bool isDead;

	sf::Vector2f velocity;
	float totalTime ;

};

