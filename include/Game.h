#pragma once

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

#include "AnimatedSprite.h"
#include "Animation.h"
#include "Bird.h"

class Game
{
public:
	Game();
	void start();

private:
	static const int SCREEN_WIDTH = 287;
	static const int SCREEN_HEIGHT = 510;

	bool isExiting(); //checks if the game is over or not
	void gameLoop(); //the main loop of the game


	enum GameState
	{
		Uninit,
		ShowingMainMenu,
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

	Bird flappy;
	GameObjects background;
	GameObjects ground;
};