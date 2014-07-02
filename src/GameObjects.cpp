#include "GameObjects.h"

GameObjects::GameObjects():
	isLoaded(false)
{}

void GameObjects::load(string imagePath)
{
	if (!texture.loadFromFile(imagePath))
		//assert statement
		cout << "ERROR" << endl;
	else
	{
		filename = imagePath;
		sprite.setTexture(texture);
		isLoaded = true;
	}
}

void GameObjects::draw(sf::RenderWindow & window)
{
	if (isLoaded)
		window.draw(sprite);
}

//to be overloaded
void GameObjects::update()
{}

void GameObjects::setPosition(float x, float y)
{
	if (isLoaded)
		sprite.setPosition(x, y);
}

sf::Vector2f GameObjects::getPosition() const
{
	if (isLoaded)
		return sprite.getPosition();
	
	return sf::Vector2f();
}

sf::Sprite & GameObjects::getSprite()
{
	return sprite;
}

bool GameObjects::loaded() const
{
	return isLoaded;
}