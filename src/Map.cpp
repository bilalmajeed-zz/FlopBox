#include "Map.h"

Map::Map()
{
	background.load("res/graphics.png", sf::IntRect(0, 0, 287, 510));

	ground[0].load("res/graphics.png", sf::IntRect(584, 0, 335, 111));
	ground[1].load("res/graphics.png", sf::IntRect(584, 0, 335, 111));
	ground[0].setPosition(0.f, 399.f);
	ground[1].setPosition(287.f, 399.f);

	pipePosY = (rand() % 260 - 350)*-1;

	for (int i = 0; i < 2; i++)
	{
		bottomPipes[i].load("res/graphics.png", sf::IntRect(112, 646, 52, 320));
		topPipes[i].load("res/graphics.png", sf::IntRect(112, 646, 52, 320));

		topPipes[i].getSprite().setOrigin(0.0f, 320.f);

		bottomPipes[i].setPosition(287 + i * spacing, pipePosY);
		topPipes[i].setPosition(287 + i * spacing, pipePosY - verticalSpacing);
	}
}

void Map::update(string object, float speed)
{
	//ground movement
	if (object == "ground")
	{
		ground[0].getSprite().move(-speed, 0.f);
		ground[1].getSprite().move(-speed, 0.f);
		if (ground[0].getPosition().x < -287)
			ground[0].setPosition(287, 399);
		else if (ground[1].getPosition().x < -287)
			ground[1].setPosition(287, 399);
	}

	//pipes movement
	if (object == "pipes")
	{
		for (int a = 0; a < 2; a++)
		{
			bottomPipes[a].getSprite().move(-speed, 0);
			topPipes[a].getSprite().move(-speed, 0);

			if (bottomPipes[a].getPosition().x < -52 && topPipes[a].getPosition().x < -52)
			{
				pipePosY = (rand() % 240 - 350)*-1;
				bottomPipes[a].setPosition(287, pipePosY);
				topPipes[a].setPosition(287, pipePosY - verticalSpacing);
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