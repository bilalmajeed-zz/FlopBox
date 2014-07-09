#include "Map.h"

Map::Map()
{
	background.load(FILEPATH, sf::IntRect(0, 0, 287, 510));

	ground[0].load(FILEPATH, sf::IntRect(584, 0, 335, 111));
	ground[1].load(FILEPATH, sf::IntRect(584, 0, 335, 111));
	ground[0].setPosition(0.f, 399.f);
	ground[1].setPosition(287.f, 399.f);

	pipePosY = (rand() % 260 - 350)*-1;

	for (int i = 0; i < 2; i++)
	{
		bottomPipes[i].load(PIPES_IMAGE, sf::IntRect(0, 0, 52, 320));
		topPipes[i].load(PIPES_IMAGE, sf::IntRect(0, 0, 52, 320));

		topPipes[i].getSprite().setOrigin(0.0f, 320.f);

		bottomPipes[i].setPosition(287 + i * spacing, pipePosY);
		topPipes[i].setPosition(287 + i * spacing, pipePosY - verticalSpacing);
	}
}

bool Map::isColliding(sf::FloatRect box)
{
	sf::FloatRect topPipe1 = topPipes[0].getSprite().getGlobalBounds();
	sf::FloatRect topPipe2 = topPipes[1].getSprite().getGlobalBounds();
	sf::FloatRect bottomPipe1 = bottomPipes[0].getSprite().getGlobalBounds();
	sf::FloatRect bottomPipe2 = bottomPipes[1].getSprite().getGlobalBounds();
	sf::FloatRect ground1 = ground[0].getSprite().getGlobalBounds();
	sf::FloatRect ground2 = ground[1].getSprite().getGlobalBounds();

	if (box.intersects(topPipe1) || box.intersects(topPipe2) ||
		box.intersects(bottomPipe1) || box.intersects(bottomPipe2) ||
		box.intersects(ground1) || box.intersects(ground2))
		return true;
	return false;

}

bool Map::isBoxThrough()
{
	int pipe1Xpos = static_cast<int>(bottomPipes[0].getPosition().x) + 26;
	int pipe2Xpos = static_cast<int>(bottomPipes[1].getPosition().x) + 26;
	int boxXpos = 82;
	
	if (boxXpos >= pipe1Xpos && count == 0)
	{
		count = 1;
		return true;
	}
	if (boxXpos >= pipe2Xpos && count == 1)
	{
		count = 2;
		return true;
	}
	if (count == 2)
		count = 0;
	return false;
	
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

void Map::reset()
{
	ground[0].setPosition(0.f, 399.f);
	ground[1].setPosition(287.f, 399.f);

	pipePosY = (rand() % 260 - 350)*-1;

	for (int i = 0; i < 2; i++)
	{
		bottomPipes[i].setPosition(287 + i * spacing, pipePosY);
		topPipes[i].setPosition(287 + i * spacing, pipePosY - verticalSpacing);
	}

	count = 0;
}