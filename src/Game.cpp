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
	ground.load("res/graphics.png", sf::IntRect(584, 0, 335, 111)); //load the ground
	flappy.load("res/graphics.png", sf::IntRect(0, 0, 1024, 1024)); //load the bird
	
	birdAnimation.setSpriteSheet(flappy.getTexture());
	birdAnimation.addFrame(sf::IntRect (174, 982, 34, 24));
	birdAnimation.addFrame(sf::IntRect(230, 658, 34, 24));
	birdAnimation.addFrame(sf::IntRect(230, 710, 34, 24));

	ground.setPosition(0.f, static_cast<float>(SCREEN_HEIGHT - 111));

	gameState = ShowingMainMenu;

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
		case ShowingMainMenu:
		{
			sf::Event menuEvent;
			while (true)
			{
				if (mainWindow.pollEvent(menuEvent))
				{
					if (menuEvent.type == sf::Event::Closed)
					{
						gameState = Exiting;
						break;
					}
					if (menuEvent.type == sf::Event::KeyPressed && menuEvent.key.code == sf::Keyboard::Space)
					{
						gameState = Playing;
						break;
					}
				}
			}
		}
		case Playing:
		{
			AnimatedSprite animatedBirdSprite(sf::seconds(0.1f), false, true);
			animatedBirdSprite.setOrigin(17, 12);
			animatedBirdSprite.setPosition(sf::Vector2f(SCREEN_WIDTH/5, SCREEN_HEIGHT/2-25));
			
			bool isSpacePressed = false;

			sf::Event currentEvent;
			while (true)
			{
				sf::Time frameTime = frameClock.restart();
				sf::Vector2f birdMove(0.f, 0.f);

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
							isSpacePressed = true;
						}

						if (currentEvent.key.code == sf::Keyboard::P)
						{
							gameState = Paused;
							break;
						}
					}
				}

				animatedBirdSprite.play(birdAnimation);

				if (isSpacePressed)
				{
					animatedBirdSprite.setRotation(-40);
					animatedBirdSprite.move(0.0f, -10000.0f * frameTime.asSeconds());
					isSpacePressed = false;
				}
				else
				{
					animatedBirdSprite.setRotation(35);
					animatedBirdSprite.move(0.0f, 80.f * frameTime.asSeconds());
				}
				

				//UPDATE
				animatedBirdSprite.update(frameTime);

				//DRAW
				background.draw(mainWindow);
				mainWindow.draw(animatedBirdSprite);
				ground.draw(mainWindow);
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