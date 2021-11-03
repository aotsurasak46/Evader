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
		scoreTopic.setPosition(sf::Vector2f(25, 100));


		_scoreText.setFont(font);
		_scoreText.setString("0");
		_scoreText.setCharacterSize(36);
		
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

	inline void UpdateScore(float deltatime,int bonus)
	{
		scoreTime += deltatime;		
		score = (scoreTime * 100 ) + bonus ;
		_scoreText.setString(std::to_string(score));
	}

	inline int getScore()
	{
		return score;
	}

private:

	sf::Text scoreTopic;
	sf::Text _scoreText;
	sf::Font font;

	float scoreTime = .0f;
	int score = 0;
	
};

