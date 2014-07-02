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

	background.load("res/graphics.png", sf::IntRect(0, 0, 287, 510)); //load bg
	flappy.load("res/graphics.png", sf::IntRect(0, 0, 1024, 1024)); //load the bird
	
	birdAnimation.setSpriteSheet(flappy.getTexture());
	birdAnimation.addFrame(sf::IntRect (174, 982, 34, 24));
	birdAnimation.addFrame(sf::IntRect(230, 658, 34, 24));
	birdAnimation.addFrame(sf::IntRect(230, 710, 34, 24));

	gameState = Playing;

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
			AnimatedSprite animatedBirdSprite(sf::seconds(0.2f), false, true);
			animatedBirdSprite.setPosition(sf::Vector2f(0, 0));

			sf::Event currentEvent;
			while (true)
			{
				sf::Time frameTime = frameClock.restart();
				animatedBirdSprite.setFrameTime(sf::seconds(0.2f));
					
				if (mainWindow.pollEvent(currentEvent))
				{
					mainWindow.clear(sf::Color::Black);

					if (currentEvent.type == sf::Event::Closed)
					{
						gameState = Exiting;
						break;
					}

					if (currentEvent.type == sf::Event::KeyPressed)
					{
						if (currentEvent.key.code == sf::Keyboard::Space)
						{
							flappy.update();
							animatedBirdSprite.setFrameTime(sf::seconds(0.05f));
						}

						if (currentEvent.key.code == sf::Keyboard::P)
						{
							gameState = Paused;
							break;
						}
					}
				}

				animatedBirdSprite.play(birdAnimation);				

				//UPDATE
				animatedBirdSprite.update(frameTime);

				//DRAW
				background.draw(mainWindow);
				mainWindow.draw(animatedBirdSprite);
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