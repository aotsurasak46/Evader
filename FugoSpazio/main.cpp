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

void ScoreBoard(string PlayerName, unsigned int PlayerScore)
{
	FILE* fp;
	char temp[255];
	unsigned int score[6];
	string name[6];
	vector<pair<unsigned int, string>> userScore;
	fp = fopen("./score.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%s", &temp);
		name[i] = temp;
		fscanf(fp, "%d", &score[i]);
		userScore.push_back(make_pair(score[i], name[i]));
	}
	name[5] = PlayerName;
	score[5] = PlayerScore;
	userScore.push_back(make_pair(score[5], name[5]));
	sort(userScore.begin(), userScore.end());
	fclose(fp);
	fopen("./score.txt", "w");
	for (int i = 5; i >= 1; i--)
	{
		strcpy(temp, userScore[i].second.c_str());
		fprintf(fp, "%s %d\n", temp, userScore[i].first);
	}
	fclose(fp);
}

void ReadScore(sf::RenderWindow &window)
{
	sf::Font font;
	if (!font.loadFromFile("font/Hypeblox-L3YGZ.ttf"))
	{
		cout << "No font is here";
	}

	sf::Text playerName[5];
	sf::Text playerScore[5];

	FILE* fp;
	char temp[255];
	unsigned int score[5];
	string name[5];
	fp = fopen("./score.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%s", &temp);
		name[i] = temp;
		fscanf(fp, "%d", &score[i]);
	}
	fclose(fp);
	for (size_t i = 0; i < 5; i++)
	{
		playerName[i].setString(name[i]);
		playerName[i].setFont(font);
		playerName[i].setCharacterSize(60);
		playerName[i].setPosition(125, 400 + 70*i);
		playerName[i].setFillColor(sf::Color::Black);

		playerScore[i].setString(std::to_string(score[i]));
		playerScore[i].setFont(font);
		playerScore[i].setCharacterSize(60);
		playerScore[i].setPosition(650, 400 + 70 * i);
		playerScore[i].setFillColor(sf::Color::Black);

		window.draw(playerName[i]);
		window.draw(playerScore[i]);
	}
}


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
	sf::Text enterNameText;

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

	enterNameText.setFont(font);
	enterNameText.setString("Enter the name");
	enterNameText.setCharacterSize(40);
	enterNameText.setFillColor(sf::Color::White);
	enterNameText.setPosition(sf::Vector2f(445, 460));


	gameOverExit.setFont(font);
	gameOverExit.setFillColor(sf::Color::Red);
	gameOverExit.setString("Press Enter to Exit");
	gameOverExit.setCharacterSize(38);
	gameOverExit.setPosition(sf::Vector2f(420,625));	

	window.draw(gameOverBackground);
	window.draw(gameOverText);
	window.draw(gameOverScore);
	window.draw(_scoreText);
	window.draw(enterNameText);
	window.draw(gameOverExit);


}

bool gameRunning;

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
	
	sf::Music gameMusic;
	sf::Music menuMusic;
	sf::Music gameOverSound;
	sf::Music scoreMusic;
	if (!gameMusic.openFromFile("sound/gameMusic.ogg"))
	{
		cout << "No Sound is here";
	}
	gameMusic.setVolume(30);
	gameMusic.setLoop(true);

	if (!menuMusic.openFromFile("sound/menuMusic.ogg"))
	{
		cout << "No Sound is here";
	}
	menuMusic.setVolume(30);
	menuMusic.setLoop(true);


	if (!gameOverSound.openFromFile("sound/gameOverSound.wav"))
	{
		cout << "No Sound is here";
	}
	gameOverSound.setVolume(30);
	gameOverSound.setLoop(false);

	if (!scoreMusic.openFromFile("sound/scoreMusic.ogg"))
	{
		cout << "No Sound is here";
	}
	scoreMusic.setVolume(30);
	scoreMusic.setLoop(true);

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

	float bulletSpawnTime = .3f;
	float itemSpawnTime = 10.0f;
	float speedBoostTime = 8.0f;
	
	
	menuMusic.play();

	
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
					menuMusic.stop();

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

						sf::String playerInput;
						sf::Text playerText;

						sf::SoundBuffer laserSoundBuffer;
						sf::SoundBuffer getItemSoundBuffer;

						sf::Sound laserSound;
						laserSoundBuffer.loadFromFile("sound/laserSound.ogg");
						sf::Sound getItemSound;
						getItemSoundBuffer.loadFromFile("sound/getItem.ogg");

						sf::Texture UFOTexture;
						UFOTexture.loadFromFile("pic/UFO.png");
						sf::Texture fireballTexture;
						fireballTexture.loadFromFile("pic/fireball.png");

						sf::Sprite UFO(UFOTexture);
						UFO.setScale(0.3, 0.3);
						UFO.setPosition(10, 700);

						sf::Sprite fireball(fireballTexture);
						fireball.setScale(0.3, 0.3);
						fireball.setPosition(20, 500);

						laserSound.setBuffer(laserSoundBuffer);
						laserSound.setLoop(false);
						laserSound.setVolume(50);

						getItemSound.setBuffer(getItemSoundBuffer);
						getItemSound.setLoop(false);
						getItemSound.setVolume(50);

						playerText.setCharacterSize(40);
						playerText.setPosition(430, 520);
						playerText.setFont(font);
						playerText.setFillColor(sf::Color::White);

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

						gameMusic.play();

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
									gameMusic.stop();
									menuMusic.play();
									break;

								case sf::Event::KeyPressed: // Press Esc to close
									if (gameEvent.key.code == sf::Keyboard::Escape)
									{
										window.close();
										gameMusic.stop();
										menuMusic.play();
									}
									break;	
								case sf::Event::KeyReleased:
									if (!gameRunning)
									{
										if (gameEvent.key.code == sf::Keyboard::Return)
										{
											window.close();
											menuMusic.play();
											if (playerInput.isEmpty())
											{
												playerInput = "Anonymous";
											}
											
											ScoreBoard(playerInput, score.getScore());
										}

									}
								case sf::Event::TextEntered:
									if (!gameRunning)
									{
										
										if (gameEvent.text.unicode > 96 && gameEvent.text.unicode < 123 && playerInput.getSize() < 15)
										{
											playerInput += gameEvent.text.unicode;
											
										}
										else if (gameEvent.key.code == sf::Keyboard::Backspace && playerInput.getSize() > 0)
										{
											playerInput.erase(playerInput.getSize() - 1);
										}

										
										playerText.setString(playerInput);

									}			
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
								itemType = randint(0,3);
								switch(itemType)
								{
								case 0:
									cupOfCoffee.push_back(Coffee(coffeeItemTexture, sf::Vector2f(randint(300, 850), randint(100, 850)), sf::Vector2f(0.25f, 0.25f)));
									break;
								case 1:
									coins.push_back(Coin(coinItemTexture, sf::Vector2f(randint(300, 850), randint(100, 850)), sf::Vector2f(0.1f, 0.1f)));
									break;
								case 2:
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
									laserSound.play();
									if (player.getHP() == 0)
									{
										gameRunning = false;
										gameOverSound.play();
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
									getItemSound.play();
								}
							}

							for (int i = 0; i < coins.size(); i++)
							{
								if (coins[i].getGlobalBounds().intersects(player.getGlobalBounds()))
								{
									coins.erase(coins.begin() + i);
									coinBonus += 2000;
									getItemSound.play();
								}

							}
							for (int i = 0; i < hearts.size(); i++)
							{
								if (hearts[i].getGlobalBounds().intersects(player.getGlobalBounds()))
								{
									
									hearts.erase(hearts.begin() + i);
									player.GainHP();
									getItemSound.play();
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
							window.draw(UFO);
							window.draw(fireball);

							if (!gameRunning)
							{							
								//Draw Gameover Menu
								DrawGameOverWindow(window,score.getScore());
								gameMusic.stop();

								window.draw(playerText);

							}

							window.display();

						}
					}


					else if (x == 1)
					{

						//--------------------------------------Score-----------------------------------------------//

						sf::RenderWindow ScoreWindow(sf::VideoMode(1000, 1000), "Scoreboard", sf::Style::Close);
						ScoreWindow.setVerticalSyncEnabled(true);

						sf::Texture scoreBoardTexture;
						sf::Texture scoreBgTexture;

						scoreBoardTexture.loadFromFile("pic/boardTexture.png");
						scoreBgTexture.loadFromFile("pic/scorebg.jpg");

						sf::Sprite scoreBg(scoreBgTexture);
						scoreBg.setScale(0.56, 0.56);

						sf::Sprite scoreBoard(scoreBoardTexture);
						scoreBoard.setScale(0.12, 0.12);
						scoreBoard.setPosition(20, 200);

						sf::Text scoreBoardText;
						scoreBoardText.setFont(font);
						scoreBoardText.setString("ScoreBoard");
						scoreBoardText.setCharacterSize(120);
						scoreBoardText.setPosition(200,25);
						scoreBoardText.setFillColor(sf::Color::Red);

						sf::Text nameText;
						nameText.setFont(font);
						nameText.setString("Name");
						nameText.setCharacterSize(70);
						nameText.setPosition(125, 300);
						nameText.setFillColor(sf::Color::Magenta);

						sf::Text scoreText;
						scoreText.setFont(font);
						scoreText.setString("Score");
						scoreText.setCharacterSize(70);
						scoreText.setPosition(650, 300);
						scoreText.setFillColor(sf::Color::Magenta);

						sf::Text backText;
						backText.setFont(font);
						backText.setString("BACK");
						backText.setCharacterSize(80);
						backText.setPosition(25, 900);
						backText.setFillColor(sf::Color::Blue);

						scoreMusic.play();

						
						while (ScoreWindow.isOpen())
						{
							sf::Event scoreboardEvent;
							while(ScoreWindow.pollEvent(scoreboardEvent))
							{
								switch (scoreboardEvent.type)
								{
								case sf::Event::Closed:
									scoreMusic.stop();
									ScoreWindow.close();
									menuMusic.play();
									break;

								case sf::Event::KeyPressed: // Press Esc to close
									if (scoreboardEvent.key.code == sf::Keyboard::Escape)
									{
										scoreMusic.stop();
										ScoreWindow.close();
										menuMusic.play();
									}
									break;
									
								case sf::Event::KeyReleased:
									if (scoreboardEvent.key.code == sf::Keyboard::Return)
									{
										scoreMusic.stop();
										ScoreWindow.close();
										menuMusic.play();
									}
									break;
								}
							}

							ScoreWindow.draw(scoreBg);
							ScoreWindow.draw(scoreBoard);
							ScoreWindow.draw(scoreBoardText);
							ScoreWindow.draw(nameText);
							ScoreWindow.draw(scoreText);
							ScoreWindow.draw(backText);
							

							ReadScore(ScoreWindow);

							ScoreWindow.display();
						}
						
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