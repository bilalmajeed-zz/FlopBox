#pragma once

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

#include "Bird.h"

class Game
{
public:
	Game();
	void start();

private:
	const int SCREEN_WIDTH = 400;
	const int SCREEN_HEIGHT = 600;

	bool isExiting(); //checks if the game is over or not
	void gameLoop(); //the main loop of the game


	enum GameState
	{
		Uninit,
		Playing,
		Paused,
		Exiting
	};
	sf::Clock clock;
	GameState gameState;
	sf::RenderWindow mainWindow;
	
	Bird flappy;

};