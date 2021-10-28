#pragma once
#include "AllHeader.h"
class Score
{

public:

	inline Score(sf::Vector2f position)
	{
		if (!font.loadFromFile("font/Hypeblox-L3YGZ.ttf"))
		{
			cout << "No font is here";
		}

		scoreTopic.setFont(font);
		scoreTopic.setString("Score");
		scoreTopic.setCharacterSize(60);
		scoreTopic.setFillColor(sf::Color::White);
		scoreTopic.setPosition(sf::Vector2f(30, 100));


		_scoreText.setFont(font);
		_scoreText.setString("0");
		_scoreText.setCharacterSize(36);
		_scoreText.setFillColor(sf::Color::White);
		_scoreText.setPosition(sf::Vector2f(10,170));

	}

	inline ~Score()
	{

	}

	inline void draw(sf::RenderWindow &window)
	{
		window.draw(scoreTopic);
		window.draw(_scoreText);
	}

	inline void UpdateScore(float deltatime)
	{
		int score = 0;
		scoreTime += deltatime;
		score = scoreTime * 100 * scoreSpeed;
		_scoreText.setString(std::to_string(score));
	}

private:

	sf::Text scoreTopic;
	sf::Text _scoreText;
	sf::Font font;
	float scoreTime = .0f;
	int scoreSpeed = 1;
	
};

