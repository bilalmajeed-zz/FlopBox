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
	
	ground[0].load("res/graphics.png", sf::IntRect(584, 0, 335, 111)); //load the ground
	ground[1].load("res/graphics.png", sf::IntRect(584, 0, 335, 111)); //load the ground
	
	bird.load("res/graphics.png", sf::IntRect(0, 0, 1024, 1024)); //load the bird
	
	birdAnimation.setSpriteSheet(bird.getTexture());
	birdAnimation.addFrame(sf::IntRect (174, 982, 34, 24));
	birdAnimation.addFrame(sf::IntRect(230, 658, 34, 24));
	birdAnimation.addFrame(sf::IntRect(230, 710, 34, 24));

	ground[0].setPosition(0.f, 399.f);
	ground[1].setPosition(287.f, 399.f);

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
			AnimatedSprite animatedBirdSprite(sf::seconds(0.1f), false, true);
			animatedBirdSprite.setOrigin(17, 12);
			animatedBirdSprite.setPosition(sf::Vector2f(SCREEN_WIDTH/5, SCREEN_HEIGHT/2-25));

			sf::Event currentEvent;
			sf::Time frameTime;
			do
			{				
				while (atMenu == 0)
				{
					animatedBirdSprite.setFrameTime(sf::seconds(0.2f));
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

					//bird flapping motion
					animatedBirdSprite.update(frameTime);

					//ground movement
					ground[0].getSprite().move(-0.07f, 0.f);
					ground[1].getSprite().move(-0.07f, 0.f);
					if (ground[0].getPosition().x < -287)
						ground[0].setPosition(287, 399);
					else if (ground[1].getPosition().x < -287)
						ground[1].setPosition(287, 399);

					//DRAW
					background.draw(mainWindow);
					mainWindow.draw(animatedBirdSprite);
					ground[0].draw(mainWindow);
					ground[1].draw(mainWindow);
					mainWindow.display();
				}
				if (atMenu != 0)
				{
					cout << "playing" << endl;
					if (mainWindow.pollEvent(currentEvent))
					{
						mainWindow.clear(sf::Color::Black);

						if (currentEvent.type == sf::Event::Closed)
						{
							gameState = Exiting;
							break;
						}

						if (currentEvent.type == sf::Event::MouseButtonPressed || currentEvent.type == sf::Event::KeyPressed)
							if (currentEvent.key.code == sf::Keyboard::Space || currentEvent.mouseButton.button == sf::Mouse::Left)
							{
								//update bird
							}
						

						if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::P)
						{
							gameState = Paused;
							break;
						}
					}

					frameTime = frameClock.restart();

					animatedBirdSprite.play(birdAnimation);

					//bird flapping motion
					animatedBirdSprite.update(frameTime);

					//ground movement
					ground[0].getSprite().move(-0.07f, 0.f);
					ground[1].getSprite().move(-0.07f, 0.f);
					if (ground[0].getPosition().x < -287)
						ground[0].setPosition(287, 399);
					else if (ground[1].getPosition().x < -287)
						ground[1].setPosition(287, 399);

					//DRAW
					background.draw(mainWindow);
					mainWindow.draw(animatedBirdSprite);
					ground[0].draw(mainWindow);
					ground[1].draw(mainWindow);
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