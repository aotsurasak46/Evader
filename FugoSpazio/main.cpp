#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"
#include "Player.h"
#include "Platform.h"
#include "Bullet.h"
#include <time.h>

int main()
{
	//Window
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Evader", sf::Style::Close | sf::Style::Resize);

	sf::Texture playerTexture;
	sf::Texture mapTexture;
	sf::Texture leftWallTexture;
	sf::Texture rightWallTexture;
	sf::Texture upperWallTexture;
	sf::Texture lowerWallTexture;
	sf::Texture cornerTexture;
	playerTexture.loadFromFile("Dog.png");
	mapTexture.loadFromFile("pic/fullfloornew.png");
	leftWallTexture.loadFromFile("pic/leftWall.png");
	rightWallTexture.loadFromFile("pic/rightWall.png");
	upperWallTexture.loadFromFile("pic/upperWall.png");
	lowerWallTexture.loadFromFile("pic/lowerWall.png");
	cornerTexture.loadFromFile("pic/image.png");
	sf::Sprite m(mapTexture);
	
	Player player(&playerTexture, sf::Vector2u(4 , 9), 0.3f,100.0f);

	std::vector<Platform> platforms;
	std::vector<Bullet> bullets;
	
	platforms.push_back(Platform(&upperWallTexture, sf::Vector2f(600.0f, 100.0f), sf::Vector2f(600.0f, 50.0f)));
	platforms.push_back(Platform(&leftWallTexture, sf::Vector2f(100.0f, 800.0f), sf::Vector2f(250.0f, 500.0f)));
	platforms.push_back(Platform(&lowerWallTexture, sf::Vector2f(600.0f, 100.0f), sf::Vector2f(600.0f, 950.0f)));
	platforms.push_back(Platform(&rightWallTexture, sf::Vector2f(100.0f, 800.0f), sf::Vector2f(950.0f, 500.0f)));
	platforms.push_back(Platform(&cornerTexture, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(250.0f, 50.0f)));
	platforms.push_back(Platform(&cornerTexture, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(950.0f, 50.0f)));
	platforms.push_back(Platform(&cornerTexture, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(250.0f, 950.0f)));
	platforms.push_back(Platform(&cornerTexture, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(950.0f, 950.0f)));
	platforms.push_back(Platform(NULL, sf::Vector2f(200.0f, 1000.0f), sf::Vector2f(100.0f, 500.0f)));
	
	float deltaTime = 0.0f;
	float totalTime = 2.0f;
	float currentTime = 0.0f;
	srand(time(NULL));
	int side ;
	float bullSpeedX ;
	float bullSpeedY ;

	sf::Clock clock;
	
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		currentTime += deltaTime;
		side = rand() % 4;

		if (currentTime >= totalTime)
		{
			
			currentTime -= totalTime;
			printf("Out");
			switch (side)
			{

			case 0:
				printf("Left\n");
				bullets.push_back(Bullet(NULL, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(0.0f, rand() % 1000)));
				bullSpeedX = 200;
				bullSpeedY = .0f;
				break;
			case 1:
				printf("Ritght\n");
				bullets.push_back(Bullet(NULL, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(1000.0f, rand() % 1000)));
				bullSpeedX = -200;
				bullSpeedY = .0f;
				break;
			case 2:
				printf("Top\n");
				bullets.push_back(Bullet(NULL, sf::Vector2f(10.0f, 100.0f), sf::Vector2f(rand() % 1000, 0.0f)));
				bullSpeedX = .0f;
				bullSpeedY = 200.0f;
				break;
			case 3:
				printf("Buttom\n");
				bullets.push_back(Bullet(NULL, sf::Vector2f(10.0f, 100.0f), sf::Vector2f(rand() % 1000,1000.0f)));
				bullSpeedX = .0f;
				bullSpeedY = -200.0f;
				break;
				
			}
		}

		sf::Event ev;

		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed: 
				window.close();
				break;

			case sf::Event::KeyPressed: //Press Esc to close
				if (ev.key.code == sf::Keyboard::Escape)
					window.close();
				break;

			}
		}
				
		
		player.Update(deltaTime);


		for (Platform& platform : platforms)
			platform.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
				
		window.clear();
		window.draw(m);
		player.Draw(window);
		
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i].Draw(window);
			bullets[i].fire(bullSpeedX * deltaTime,bullSpeedY * deltaTime);

			if (bullets[i].GetCollider().CheckCollision(player.GetCollider(), NULL))
			{
				bullets.erase(bullets.begin() + i);
			}

			else if (bullets[i].getPos().x > 1000)
			{
				bullets.erase(bullets.begin() + i);
			}
		}
		
		for (Platform& platform : platforms)
			platform.Draw(window);

		window.display();
	}
	return 0;
}