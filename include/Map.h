#pragma once

#include <cstdlib>

#include "GameObjects.h"

class Map
{
public:
	Map();
	bool isColliding(sf::FloatRect bird);
	void update(string object, float speed);
	void draw(sf::RenderWindow & window, int atMenu);
	
	int configNum;

private:
	const string FILEPATH = "res/graphics.png";
	GameObjects background;
	GameObjects ground[2];
	GameObjects bottomPipes[2];
	GameObjects topPipes[2];
	int pipePosY;
	int spacing = 160;
	int verticalSpacing = 90;

};