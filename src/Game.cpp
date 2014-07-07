#include "Game.h"

Game::Game()
{
	gameState = Uninit;
}

void Game::start()
{
	if (gameState != Uninit)
		return;

	srand(time(NULL));
	mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flap Those Wings", sf::Style::Titlebar | sf::Style::Close);
	mainWindow.setPosition(sf::Vector2i(400, 10));

	bird.load("res/graphics.png", sf::IntRect(0, 0, 1024, 1024)); //load the bird
	
	birdAnimation.setSpriteSheet(bird.getTexture());
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
			animatedBirdSprite.setOrigin(17, 12);
			animatedBirdSprite.setPosition(sf::Vector2f(SCREEN_WIDTH/5, SCREEN_HEIGHT/2-25));
			
			int speed = 100;
			float birdmoveY = 0.0f;
			int birdRotatation = 0;
			sf::Event currentEvent;
			sf::Time frameTime;
			do
			{				
				while (atMenu == 0)
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
							if (currentEvent.key.code == sf::Keyboard::Space || currentEvent.mouseButton.button == sf::Mouse::Left)
							{
								atMenu = 1;
								isReady = true;
								break;
							}
						}
					}

					frameTime = frameClock.restart();

					animatedBirdSprite.play(birdAnimation);

					//UPDATE
					map.update("ground", speed * frameTime.asSeconds());
					animatedBirdSprite.update(frameTime); //bird flapping motion

					//DRAW
					map.draw(mainWindow, atMenu);
					mainWindow.draw(animatedBirdSprite);
					mainWindow.display();
				}
				if (atMenu != 0)
				{
					animatedBirdSprite.setFrameTime(sf::seconds(0.15f));
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
								if (animatedBirdSprite.getPosition().y <= 150)
									birdmoveY -= birdmoveY + 0.99;
								else
									birdmoveY -= birdmoveY + 0.9;

								birdRotatation = -45;
								
								keyPressed = true;
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

					if (animatedBirdSprite.getPosition().y <= 100)
						comingFromHighPos = true;
					else
						comingFromHighPos = false;

					frameTime = frameClock.restart();
					animatedBirdSprite.play(birdAnimation);

					if (birdmoveY < 0.1f && !keyPressed)
					{
						if (comingFromHighPos)
							birdmoveY += (0.09);
						else
							birdmoveY += (0.04);

					}
					else if (birdmoveY < 0.1f && keyPressed)
					{
						birdmoveY += (0.01);
					}

					if (!keyPressed)
					{
						birdRotatation = 45;
					}
					animatedBirdSprite.move(0.0f, birdmoveY);
					animatedBirdSprite.setRotation(birdRotatation);
					
					//UPDATE
					map.update("ground", speed * frameTime.asSeconds()); //ground movement
					map.update("pipes", speed * frameTime.asSeconds()); //pipes movement
					animatedBirdSprite.update(frameTime); //bird flapping motoin

					//DRAW
					map.draw(mainWindow, atMenu);
					mainWindow.draw(animatedBirdSprite);
					mainWindow.display();
				}
			
			}while (isReady);
			
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