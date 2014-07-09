#pragma once

#include <cstdlib>

#include "GameObjects.h"

class Map
{
public:
	Map();
	bool isColliding(sf::FloatRect box);
	bool isBoxThrough();
	void update(string object, float speed);
	void draw(sf::RenderWindow & window, int atMenu);
	void reset();

private:
	const string FILEPATH = "res/graphics.png";
	const string PIPES_IMAGE = "res/pipes.png";
	GameObjects background;
	GameObjects ground[2];
	GameObjects bottomPipes[2];
	GameObjects topPipes[2];
	int pipePosY;
	int spacing = 160;
	int verticalSpacing = 110;
	int count = 0;

};