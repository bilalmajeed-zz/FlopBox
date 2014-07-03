#include "Map.h"

Map::Map()
{
	background.load("res/graphics.png", sf::IntRect(0, 0, 287, 510));

	ground[0].load("res/graphics.png", sf::IntRect(584, 0, 335, 111));
	ground[1].load("res/graphics.png", sf::IntRect(584, 0, 335, 111));
	ground[0].setPosition(0.f, 399.f);
	ground[1].setPosition(287.f, 399.f);

	configurations[0] = sf::Vector2f(333, 250);
	configurations[1] = sf::Vector2f(240, 157);
	configurations[2] = sf::Vector2f(151, 68);
	
	for (int i = 0; i < 2; i++)
	{
		bottomPipes[i].load("res/graphics.png", sf::IntRect(112, 646, 52, 320));
		topPipes[i].load("res/graphics.png", sf::IntRect(112, 646, 52, 320));
		topPipes[i].getSprite().setOrigin(0.0f, 320.f);
			

		bottomPipes[i].setPosition(287 + i * spacing, configurations[1].x);
		topPipes[i].setPosition(287 + i * spacing, configurations[1].y);
	}
}

void Map::update(string object)
{
	//ground movement
	if (object == "ground")
	{
		ground[0].getSprite().move(-0.07f, 0.f);
		ground[1].getSprite().move(-0.07f, 0.f);
		if (ground[0].getPosition().x < -287)
			ground[0].setPosition(287, 399);
		else if (ground[1].getPosition().x < -287)
			ground[1].setPosition(287, 399);
	}

	//pipes movement
	if (object == "pipes")
	{
		for (int i = 0; i <= 2; i++)
		{
			bottomPipes[i].getSprite().move(-0.07f, 0);
			topPipes[i].getSprite().move(-0.07f, 0);

			if (bottomPipes[i].getPosition().x < -52 && topPipes[i].getPosition().x < -52)
			{
				configNum = rand() % 3;
				bottomPipes[i].setPosition(287, configurations[configNum].x);
				topPipes[i].setPosition(287, configurations[configNum].y);
			}
		}
	}
}

void Map::draw(sf::RenderWindow & window, int atMenu)
{
	background.draw(window);
	if (atMenu != 0)
	{
		bottomPipes[0].draw(window);
		bottomPipes[1].draw(window);

		topPipes[0].draw(window);
		topPipes[1].draw(window);
	}
	ground[0].draw(window);
	ground[1].draw(window);
}