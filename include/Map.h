#pragma once

#include <cstdlib>

#include "GameObjects.h"

class Map
{
public:
	Map();
	void update(string object);
	void draw(sf::RenderWindow & window, int atMenu);
	
	int configNum;

private:
	GameObjects background;
	GameObjects ground[2];
	GameObjects bottomPipes[2];
	GameObjects topPipes[2];
	sf::Vector2f configurations[3];
	int pipePosY;
	int spacing = 160;
	int verticalSpacing = 83;

};