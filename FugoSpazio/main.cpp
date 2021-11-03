#include "AllHeader.h"
#include "Animation.h"
#include "Player.h"
#include "Platform.h"
#include "Bullet.h"
#include "MainMenu.h"
#include "Score.h"
#include "Coffee.h"
#include "Coin.h"
#include "Heart.h"
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



bool gameRunning ;

void gameOver()
{
	gameRunning = false;

}


void DrawGameOverWindow(sf::RenderWindow& window,unsigned int score)
{
	sf::Font font;
	if (!font.loadFromFile("font/Hypeblox-L3YGZ.ttf"))
	{
		cout << "No font is here";
	}

	sf::RectangleShape gameOverBackground;
	sf::Texture gameOverBackgroundTexture;

	gameOverBackgroundTexture.loadFromFile("pic/gameOverBG.jpg");

	sf::Text gameOverText;
	sf::Text gameOverScore;
	sf::Text _scoreText;
	sf::Text gameOverExit;

	gameOverBackground.setPosition(sf::Vector2f(400,300));
	gameOverBackground.setSize(sf::Vector2f(400,400));
	gameOverBackground.setTexture(&gameOverBackgroundTexture);

	gameOverText.setFont(font);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setString("GAMEOVER");
	gameOverText.setCharacterSize(60);
	gameOverText.setPosition(sf::Vector2f(470, 320));

	gameOverScore.setFont(font);
	gameOverScore.setFillColor(sf::Color::Red);
	gameOverScore.setString("Score : ");
	gameOverScore.setCharacterSize(56);
	gameOverScore.setPosition(sf::Vector2f(420 ,390));

	_scoreText.setFont(font);
	_scoreText.setString(std::to_string(score));
	_scoreText.setCharacterSize(40);
	_scoreText.setFillColor(sf::Color::Red);
	_scoreText.setPosition(sf::Vector2f(610, 403));

	gameOverExit.setFont(font);
	gameOverExit.setFillColor(sf::Color::Red);
	gameOverExit.setString("Press ESC to Exit");
	gameOverExit.setCharacterSize(42);
	gameOverExit.setPosition(sf::Vector2f(425,620));	

	window.draw(gameOverBackground);
	window.draw(gameOverText);
	window.draw(gameOverScore);
	window.draw(_scoreText);
	window.draw(gameOverExit);


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

	sf::Texture coffeeItemTexture;
	sf::Texture coinItemTexture;
	sf::Texture heartItemTexture;
	
	sf::Font font;
	if (!font.loadFromFile("font/Hypeblox-L3YGZ.ttf"))
	{
		cout << "No font is here";
	}

	playerTexture.loadFromFile("pic/NewDogV2.png");
	mapTexture.loadFromFile("pic/fullfloornew.png");
	leftWallTexture.loadFromFile("pic/leftWall.png");
	rightWallTexture.loadFromFile("pic/rightWall.png");
	upperWallTexture.loadFromFile("pic/upperWall.png");
	lowerWallTexture.loadFromFile("pic/lowerWall.png");
	cornerTexture.loadFromFile("pic/image.png");
	mainMenuBg.loadFromFile("pic/space.jpg");
	gameMenuBg.loadFromFile("pic/game_menu_bg1.jpg");
	
	coffeeItemTexture.loadFromFile("pic/coffee.png");
	coinItemTexture.loadFromFile("pic/coin.png");
	heartItemTexture.loadFromFile("pic/heartitem.png");

	sf::Sprite m(mapTexture);
	sf::Sprite mainbg(mainMenuBg);
	
	
	float deltaTime = 0.0f;


	float currentTimeBullet = 0.0f;
	float currentTimeItem = 0.0f;
	float currentTimeSpeedBoost = 0.0f;

	float bulletSpawnTime = .4f;
	float itemSpawnTime = 20.0f;
	float speedBoostTime = 10.0f;

	
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

						Player player(&playerTexture, sf::Vector2u(4, 5), 0.3f, 200.0f);

						Score score(sf::Vector2f(10,120));

						std::vector<Bullet> bullets;
						std::vector<Platform> platforms;
						std::vector<Coffee> cupOfCoffee;
						std::vector<Coin> coins;
						std::vector<Heart> hearts;

						platforms.push_back(Platform(&upperWallTexture, sf::Vector2f(600.0f, 100.0f), sf::Vector2f(600.0f, 50.0f)));
						platforms.push_back(Platform(&leftWallTexture, sf::Vector2f(100.0f, 800.0f), sf::Vector2f(250.0f, 500.0f)));
						platforms.push_back(Platform(&lowerWallTexture, sf::Vector2f(600.0f, 100.0f), sf::Vector2f(600.0f, 950.0f)));
						platforms.push_back(Platform(&rightWallTexture, sf::Vector2f(100.0f, 800.0f), sf::Vector2f(950.0f, 500.0f)));
						platforms.push_back(Platform(&cornerTexture, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(250.0f, 50.0f)));
						platforms.push_back(Platform(&cornerTexture, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(950.0f, 50.0f)));
						platforms.push_back(Platform(&cornerTexture, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(250.0f, 950.0f)));
						platforms.push_back(Platform(&cornerTexture, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(950.0f, 950.0f)));
						platforms.push_back(Platform(&gameMenuBg, sf::Vector2f(200.0f, 1000.0f), sf::Vector2f(100.0f, 500.0f)));

						int itemType;
						int coinBonus = 0;
						bool isSpeedBoost = false;

						gameRunning = true;

						sf::Clock clock;
						while (window.isOpen())
						{

							deltaTime = clock.restart().asSeconds() * gameRunning ;

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
							

							//Spawn Bullet
							currentTimeBullet += deltaTime;
							if (currentTimeBullet >= bulletSpawnTime)
							{
								currentTimeBullet -= bulletSpawnTime;
								spawnBullet(bullets);
							}


							//Spawn Item
							currentTimeItem += deltaTime;
							if (currentTimeItem >= itemSpawnTime)
							{
								currentTimeItem -= itemSpawnTime;
								cout << "Item Spawn";
								itemType = randint(0,3);
								switch(itemType)
								{
								case 0:
									cout << "Coffee\n";
									cupOfCoffee.push_back(Coffee(coffeeItemTexture, sf::Vector2f(randint(300, 850), randint(100, 850)), sf::Vector2f(0.25f, 0.25f)));
									break;
								case 1:
									cout << "Coin\n";
									coins.push_back(Coin(coinItemTexture, sf::Vector2f(randint(300, 850), randint(100, 850)), sf::Vector2f(0.1f, 0.1f)));
									break;
								case 2:
									cout << "Heart\n";
									hearts.push_back(Heart(heartItemTexture, sf::Vector2f(randint(300, 850), randint(100, 850)), sf::Vector2f(0.1f, 0.1f)));
									break;
								default:
									break;
								}	
							}

							score.UpdateScore(deltaTime,coinBonus);
							player.Update(deltaTime,isSpeedBoost);

							//Bullet Update
							for (int i = 0; i < bullets.size(); i++)
							{
								bullets[i].Update(deltaTime);

								// if (bullets[i].GetCollider().CheckCollision(player.GetCollider(), NULL))
								if (bullets[i].getGlobalBounds().intersects(player.getGlobalBounds()))
								{
									bullets.erase(bullets.begin() + i);
									player.LooseHP();
									if (player.getHP() == 0)
									{
										gameOver();	
										
									}
								}
								else if (bullets[i].isOutOfScreen())
								{
									bullets.erase(bullets.begin() + i);
								}
							}

							//Item Update
							
							for (int i = 0; i < cupOfCoffee.size(); i++)
							{
								if (cupOfCoffee[i].getGlobalBounds().intersects(player.getGlobalBounds()))
								{
									cupOfCoffee.erase(cupOfCoffee.begin() + i);
									isSpeedBoost = true;
								}
							}

							for (int i = 0; i < coins.size(); i++)
							{
								if (coins[i].getGlobalBounds().intersects(player.getGlobalBounds()))
								{
									coins.erase(coins.begin() + i);
									coinBonus += 2000;
								}

							}
							for (int i = 0; i < hearts.size(); i++)
							{
								if (hearts[i].getGlobalBounds().intersects(player.getGlobalBounds()))
								{
									hearts.erase(hearts.begin() + i);
									player.GainHP();
								}
							}

							if (isSpeedBoost)
							{
								currentTimeSpeedBoost += deltaTime;
								if (currentTimeSpeedBoost >= speedBoostTime)
								{
									currentTimeSpeedBoost -= speedBoostTime;
									isSpeedBoost = false;
								}
							}

							//Platform Update
							for (Platform& platform : platforms)
								platform.GetCollider().CheckCollision(player.GetCollider(), 1.0f);


							// ↓ Drawing Part
							window.clear();
							window.draw(m);

							for (int i = 0; i < cupOfCoffee.size(); i++)
							{
								cupOfCoffee[i].drawCoffee(window);
								
							}

							for (int i = 0; i < coins.size(); i++)
							{
								coins[i].drawCoin(window);

							}

							for (int i = 0; i < hearts.size(); i++)
							{	
								hearts[i].drawHeart(window);

							}


							for (int i = 0; i < bullets.size(); i++)
							{
								bullets[i].Draw(window);
							}
							player.Draw(window);

							for (Platform& platform : platforms)
								platform.Draw(window);

							score.draw(window);
							player.drawHeart(window);

							


							if (!gameRunning)
							{							
								//Draw Gameover Menu
								DrawGameOverWindow(window,score.getScore());
							}

							window.display();

						}
					}


					else if (x == 1)
					{

						//--------------------------------------Score-----------------------------------------------//

						sf::RenderWindow ScoreWindow(sf::VideoMode(1000, 1000), "Scoreboard", sf::Style::Close);


						while (ScoreWindow.isOpen())
						{
							sf::Event scoreboardEvent;
							switch (ScoreWindow.pollEvent(scoreboardEvent))
							{
							case sf::Event::Closed:
								ScoreWindow.close();
								break;

							case sf::Event::KeyPressed: // Press Esc to close
								if (scoreboardEvent.key.code == sf::Keyboard::Escape)
								{
									ScoreWindow.close();
								}
								break;
							}

						}




						
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