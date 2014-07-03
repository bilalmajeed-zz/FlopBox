#pragma once

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

#include "AnimatedSprite.h"
#include "Animation.h"
#include "GameObjects.h"

class Game
{
public:
	Game();
	void start();

private:
	static const int SCREEN_WIDTH = 287;
	static const int SCREEN_HEIGHT = 510;
	int atMenu = 0;
	int firstFly = 1;
	bool isReady = false; 

	bool isExiting(); //checks if the game is over or not
	void gameLoop(); //the main loop of the game


	enum GameState
	{
		Uninit,
		Playing,
		Paused,
		Exiting
	};

	//from the sfml libraries
	sf::Clock frameClock;
	GameState gameState;
	sf::RenderWindow mainWindow;

	//from animation library by LaurentGomila
	Animation birdAnimation;

	GameObjects bird;
	GameObjects background;
	GameObjects ground[2];
};