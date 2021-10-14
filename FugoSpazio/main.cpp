#include "AllHeader.h"
#include "Animation.h"
#include "Player.h"
#include "Platform.h"
#include "Bullet.h"
#include <time.h>

void spawnBullet(vector<Bullet>& bullets)
{
	int side = rand() % 4;
	Vector2f bulletSize;
	Vector2f spawnPos;
	Vector2f direction;
	switch (side)
	{
	case 0: // Left
		bulletSize = Vector2f(100.0f, 10.0f);
		spawnPos = Vector2f(0.0f, randint(100, 900 - bulletSize.y));
		direction = Vector2f(1, 0);
		break;
	case 1: // Right
		bulletSize = Vector2f(100.0f, 10.0f);
		spawnPos = Vector2f(1000.0f, randint(100, 900 - bulletSize.y));
		direction = Vector2f(-1, 0);
		break;
	case 2: // Top
		bulletSize = Vector2f(10.0f, 100.0f);
		spawnPos = Vector2f(randint(300, 900 - bulletSize.x), 0);
		direction = Vector2f(0, 1);
		break;
	case 3: // Down
		bulletSize = Vector2f(10.0f, 100.0f);
		spawnPos = Vector2f(randint(300, 900 - bulletSize.x), 1000);
		direction = Vector2f(0, -1);
		break;
	default:
		break;
	}
	bullets.push_back(Bullet(nullptr, bulletSize, spawnPos, direction, 300));
}

int main()
{
	//Window
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Evader", sf::Style::Close | sf::Style::Resize);
	srand(time(NULL));
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

	std::vector<Bullet> bullets;
	
	std::vector<Platform> platforms;
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

	sf::Clock clock;
	
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		sf::Event ev;
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed: // Press Esc to close
				if (ev.key.code == sf::Keyboard::Escape)
					window.close();
				break;
			}
		}
		// ↓ Update Part
		currentTime += deltaTime;
		if (currentTime >= totalTime)
		{
			currentTime -= totalTime;
			spawnBullet(bullets);
		}
		
		player.Update(deltaTime);

		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i].Update(deltaTime);
			
			// if (bullets[i].GetCollider().CheckCollision(player.GetCollider(), NULL))
			if (bullets[i].getGlobalBounds().intersects(player.getGlobalBounds()))
			{
				bullets.erase(bullets.begin() + i);
			}
			else if (bullets[i].isOutOfScreen())
			{
				bullets.erase(bullets.begin() + i);
			}
		}

		for (Platform& platform : platforms)
			platform.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
		
		// ↓ Drawing Part
		window.clear();
		window.draw(m);
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i].Draw(window);
		}
		player.Draw(window);
		for (Platform& platform : platforms)
			platform.Draw(window);
		window.display();
	}
	return 0;
}