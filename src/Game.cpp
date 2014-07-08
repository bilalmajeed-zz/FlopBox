#include "Game.h"

Game::Game()
{
	gameState = Uninit;
}

void Game::start()
{
	if (gameState != Uninit)
		return;

	srand(static_cast<unsigned>(time(NULL)));
	mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flap The Wings", sf::Style::Titlebar | sf::Style::Close);
	mainWindow.setPosition(sf::Vector2i(400, 10));

	box.load(BOX_IMAGE, sf::IntRect(0, 0, 24, 24)); //load the box
	box.getSprite().setOrigin(12, 12);
	box.setPosition(SCREEN_WIDTH / 5 + 25, SCREEN_HEIGHT / 2 - 25);

	getReady.load(FILE_PATH, sf::IntRect(590, 116, 184, 52));
	getReady.setPosition(50, 89);
	instructions.load(FILE_PATH, sf::IntRect(583, 182, 114, 98));
	instructions.setPosition(80, 200);

	gameState = Menu;

	while (!isExiting())
		gameLoop();

	mainWindow.close();
}

bool Game::isExiting()
{
	if (gameState == Exiting)
		return true;
	return false;
}

void Game::gameLoop()
{
	int speed = 100;
	float birdmoveY = 0.0f;

	sf::Event currentEvent;
	sf::Time frameTime;

	switch (gameState)
	{
		case Menu:
		{
			while (true)
			{
				if (mainWindow.pollEvent(currentEvent))
				{
					mainWindow.clear(sf::Color::Black);

					if (currentEvent.type == sf::Event::Closed)
					{
						gameState = Exiting;
						break;
					}
					if (currentEvent.type == sf::Event::MouseButtonPressed)
					{
						if (currentEvent.mouseButton.button == sf::Mouse::Left)
						{
							gameState = Playing;
							break;
						}
					}
				}

				frameTime = frameClock.restart();

				//UPDATE
				map.update("ground", speed * frameTime.asSeconds());

				//DRAW
				map.draw(mainWindow, 0);
				box.draw(mainWindow);
				getReady.draw(mainWindow);
				instructions.draw(mainWindow);
				mainWindow.display();
			}
		}
	
		case Playing:
		{
			while (true)
			{
				if (mainWindow.pollEvent(currentEvent))
				{
					mainWindow.clear(sf::Color::Black);

					if (currentEvent.type == sf::Event::Closed)
					{
						gameState = Exiting;
						break;
					}

					if (currentEvent.type == sf::Event::MouseButtonPressed || currentEvent.type == sf::Event::KeyPressed)
					{
						if ((currentEvent.mouseButton.button == sf::Mouse::Left || currentEvent.key.code == sf::Keyboard::Space) && !keyPressed)
						{
							//bird up and down movements
							if (box.getPosition().y <= 150)
								birdmoveY -= birdmoveY + 0.89f;
							else
								birdmoveY -= birdmoveY + 0.8f;

							keyPressed = true;
							flapping = true;
						}
						else
						{
							keyPressed = false;
						}
					}
					else
					{
						keyPressed = false;
					}

				}

				frameTime = frameClock.restart();

				if (birdmoveY < 0.1f && !keyPressed)
					birdmoveY += (0.08f);
				else if (birdmoveY < 0.1f && keyPressed)
					birdmoveY += (0.01f);

				box.getSprite().move(0.0f, birdmoveY);

				if (map.isColliding(box.getSprite().getGlobalBounds()))
				{
					gameState = Exiting;
					break;
				}

				//UPDATE
				map.update("ground", speed * frameTime.asSeconds()); //ground movement
				map.update("pipes", speed * frameTime.asSeconds()); //pipes movement

				//DRAW
				map.draw(mainWindow, 1);
				box.draw(mainWindow);
				mainWindow.display();
			}
			break;
		}
	
		case Paused:
		{
			while (true)
			{
				sf::Event pauseEvent;
				if (mainWindow.pollEvent(pauseEvent))
					if (pauseEvent.type == sf::Event::KeyPressed)
						if (pauseEvent.key.code == sf::Keyboard::P)
							gameState = Playing;
				break;
			}
			break;
		}
	}
}