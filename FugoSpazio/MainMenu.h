#pragma once
#include "AllHeader.h"
#define MAX_MAINMENU 3
class MainMenu
{

public:
	inline MainMenu(float width, float height)
	{
		if (!font.loadFromFile("font/Hypeblox-L3YGZ.ttf"))
		{
			cout << "No font is here";
		}
		//Game Name
		gameName.setFont(font);
		gameName.setFillColor(sf::Color::Red);
		gameName.setString("DOGDAK");
		gameName.setCharacterSize(250);
		gameName.setPosition(100, 0);

		//Play
		mainMenu[0].setFont(font);
		mainMenu[0].setFillColor(sf::Color::Blue);
		mainMenu[0].setString("Play");
		mainMenu[0].setCharacterSize(200);
		mainMenu[0].setPosition(50, 300);
		//Score
		mainMenu[1].setFont(font);
		mainMenu[1].setFillColor(sf::Color::White);
		mainMenu[1].setString("Score");
		mainMenu[1].setCharacterSize(200);
		mainMenu[1].setPosition(50, 500);
		//Exit
		mainMenu[2].setFont(font);
		mainMenu[2].setFillColor(sf::Color::White);
		mainMenu[2].setString("Exit");
		mainMenu[2].setCharacterSize(200);
		mainMenu[2].setPosition(50, 700);

		MainMenuSelected = 0;
	}

	inline ~MainMenu()
	{
	}

	inline void draw(sf::RenderWindow& window)
	{
		sf::Texture dogmenu;
		dogmenu.loadFromFile("pic/DogMenu.png");

		sf::RectangleShape dog;
		dog.setPosition(sf::Vector2f(600, 400));
		dog.setSize(sf::Vector2f(400, 400));
		dog.setTexture(&dogmenu);

		for (int i = 0; i < MAX_MAINMENU; i++)
		{
			window.draw(mainMenu[i]);
		}
		window.draw(gameName);
		window.draw(dog);
	}

	inline void MoveUp()
	{
		MainMenuSelected -= 1;
		if (MainMenuSelected < 0)
		{
			MainMenuSelected = 2;
			mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);
			mainMenu[0].setFillColor(sf::Color::White);

		}
		else
		{
			mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);
			mainMenu[MainMenuSelected+1].setFillColor(sf::Color::White);
		}
	}

	inline void MoveDown()
	{
		MainMenuSelected += 1;
		if (MainMenuSelected > 2)
		{
			MainMenuSelected = 0;
			mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);
			mainMenu[2].setFillColor(sf::Color::White);
		}
		else
		{
			mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);
			mainMenu[MainMenuSelected - 1].setFillColor(sf::Color::White);
		}

		
	}

	int MainMenuPressed() { return MainMenuSelected; }


private:

	int MainMenuSelected = 0;
	sf::Font font;
	sf::Text mainMenu[MAX_MAINMENU];
	sf::Text gameName;

};

