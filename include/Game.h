#pragma once

#include <iostream>
#include <time.h>
#include <sstream>
#include <assert.h>

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

#include "GameObjects.h"
#include "Map.h"

class Game
{
public:
	Game();
	void start();

private:	
	static const int SCREEN_WIDTH = 287;
	static const int SCREEN_HEIGHT = 510;
	const string FILE_PATH = "res/graphics.png";
	const string BOX_IMAGE = "res/box.png";
	
	bool keyPressed = false;
	int count = 1;
	int score = 0;
	sf::Font font;

	bool isExiting(); //checks if the game is over or not
	void gameLoop(); //the main loop of the game
	
	void updateScore();
	void drawScore(sf::RenderWindow & window);

	void reset();

	enum GameState
	{
		Uninit,
		Menu,
		Playing,
		GameOver,
		Exiting
	};

	//from the sfml libraries
	sf::Clock frameClock;
	GameState gameState;
	sf::RenderWindow mainWindow;

	GameObjects box;
	Map map;
};