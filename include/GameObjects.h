#pragma once

#include "SFML\Graphics.hpp"
#include <iostream>
#include <string>
using namespace std;

class GameObjects
{
public:
	GameObjects();
	
	void load(string imagePath);
	void draw(sf::RenderWindow & window);

	virtual void update();

	void setPosition(float x, float y); //sets position of object
	sf::Vector2f getPosition() const; //gets position of the object

	sf::Sprite & getSprite(); //gets sprite, in order to access other memeber functions
	
protected:
	virtual bool loaded() const;

private:
	sf::Texture texture;
	sf::Sprite sprite;
	string filename;
	bool isLoaded;
};