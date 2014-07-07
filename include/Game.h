#pragma once

#include <iostream>
#include <time.h>

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

#include "AnimatedSprite.h"
#include "Animation.h"
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
	bool keyPressed = false;
	bool comingFromHighPos = false;
	bool flapping = true;

	bool isExiting(); //checks if the game is over or not
	void gameLoop(); //the main loop of the game


	enum GameState
	{
		Uninit,
		Menu,
		Playing,
		Paused,
		Exiting
	};

	//from the sfml libraries
	sf::Clock frameClock;
	GameState gameState;
	sf::RenderWindow mainWindow;

	Animation birdAnimation; //from animation library by LaurentGomila
	GameObjects bird;
	GameObjects getReady;
	GameObjects instructions;
	Map map;
};