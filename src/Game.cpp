#include "Game.h"

Game::Game()
{
	gameState = Uninit;
}

void Game::start()
{
	if (gameState != Uninit)
		return;

	mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flap Those Wings", sf::Style::Titlebar | sf::Style::Close);
	mainWindow.setPosition(sf::Vector2i(400, 10));

	gameState = Playing;

	//while the game is still running go the game loop
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
	switch (gameState)
	{
		case Playing:
		{
			sf::Time elaspedTime = clock.restart();

			sf::Event currentEvent;
			while (true)
			{
				if (mainWindow.pollEvent(currentEvent))
				{
					mainWindow.setMouseCursorVisible(false);
					mainWindow.clear(sf::Color::Black);

					//if the exit button is clicked
					if (currentEvent.type == sf::Event::Closed)
					{
						gameState = Exiting;
						break;
					}

					//if a keyboard button is pressed
					if (currentEvent.type == sf::Event::KeyPressed)
					{
						//pressed SPACEBAR
						if (currentEvent.key.code == sf::Keyboard::Space)
						{
							//move the bird up
						}

						//pressed P
						if (currentEvent.key.code == sf::Keyboard::P)
						{
							gameState = Paused;
							break;
						}
					}
				}

				//UPDATE AND DRAW
				flappy.draw(mainWindow);
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