#include "AllHeader.h"
#include "Animation.h"
#include "Player.h"
#include "Platform.h"
#include "Bullet.h"
#include "MainMenu.h"
#include "Score.h"
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
	bullets.push_back(Bullet( bulletSize, spawnPos, direction, 300));
}

int main()
{
	//Main Menu
	sf::RenderWindow Menu(sf::VideoMode(1000, 1000), "MainMenu", sf::Style::Close);
	
	srand(time(NULL));

	MainMenu mainMenu(Menu.getSize().x, Menu.getSize().y);

	sf::Texture playerTexture;
	sf::Texture mapTexture;
	sf::Texture leftWallTexture;
	sf::Texture rightWallTexture;
	sf::Texture upperWallTexture;
	sf::Texture lowerWallTexture;
	sf::Texture cornerTexture;
	sf::Texture mainMenuBg;
	sf::Texture gameMenuBg;
	

	playerTexture.loadFromFile("pic/NewDogV2.png");
	mapTexture.loadFromFile("pic/fullfloornew.png");
	leftWallTexture.loadFromFile("pic/leftWall.png");
	rightWallTexture.loadFromFile("pic/rightWall.png");
	upperWallTexture.loadFromFile("pic/upperWall.png");
	lowerWallTexture.loadFromFile("pic/lowerWall.png");
	cornerTexture.loadFromFile("pic/image.png");
	mainMenuBg.loadFromFile("pic/space.jpg");
	gameMenuBg.loadFromFile("pic/game_menu_bg1.jpg");
	

	sf::Sprite m(mapTexture);
	sf::Sprite mainbg(mainMenuBg);
	
	
	float deltaTime = 0.0f;

	float totalTime = .4f;

	float currentTime = 0.0f;

	
	
	while (Menu.isOpen())
	{
		sf::Event menuEvent;
		while (Menu.pollEvent(menuEvent))
		{
			switch (menuEvent.type)
			{
			case sf::Event::Closed:
				Menu.close();
				break;

			case sf::Event::KeyPressed: // Press Esc to close
				if (menuEvent.key.code == sf::Keyboard::Escape)
					Menu.close();
				break;

			case sf::Event::KeyReleased:
				switch (menuEvent.key.code)
				{
				case sf::Keyboard::Up:
					mainMenu.MoveUp();
					break;

				case sf::Keyboard::Down:
					mainMenu.MoveDown();
					break;

				case sf::Keyboard::Return:
					int x = mainMenu.MainMenuPressed();


					if (x == 0)
					{
						
						//--------------------------------GameWindow-------------------------------------//


						sf::RenderWindow window(sf::VideoMode(1000, 1000), "Evader", sf::Style::Close);
						window.setVerticalSyncEnabled(true);

						Player player(&playerTexture, sf::Vector2u(4, 5), 0.3f, 180.0f);

						Score score(sf::Vector2f(10,120));

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
						platforms.push_back(Platform(&gameMenuBg, sf::Vector2f(200.0f, 1000.0f), sf::Vector2f(100.0f, 500.0f)));


						sf::Clock clock;
						while (window.isOpen())
						{

							deltaTime = clock.restart().asSeconds();

							sf::Event gameEvent;
							while (window.pollEvent(gameEvent))
							{
								switch (gameEvent.type)
								{
								case sf::Event::Closed:
									window.close();
									break;

								case sf::Event::KeyPressed: // Press Esc to close
									if (gameEvent.key.code == sf::Keyboard::Escape)
									{
										window.close();
									}
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

							score.UpdateScore(deltaTime);
							player.Update(deltaTime);

							for (int i = 0; i < bullets.size(); i++)
							{
								bullets[i].Update(deltaTime);

								// if (bullets[i].GetCollider().CheckCollision(player.GetCollider(), NULL))
								if (bullets[i].getGlobalBounds().intersects(player.getGlobalBounds()))
								{
									bullets.erase(bullets.begin() + i);
									player.LooseHP();
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

							score.draw(window);
							player.drawHeart(window);
							window.display();
						}
					}


					else if (x == 1)
					{

						//--------------------------------------Score-----------------------------------------------//

						sf::RenderWindow ScoreWindow(sf::VideoMode(1000, 1000), "Scoreboard", sf::Style::Close);


						ScoreWindow.clear();
						ScoreWindow.display();
					}

					else if (x == 2)
					{
						Menu.close();
					}
				}
			}
		}
	

		Menu.clear();
		Menu.draw(mainbg);
		mainMenu.draw(Menu);
		Menu.display();
	}


	return 0;
}