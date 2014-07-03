#include "Bird.h"
#include <assert.h>

void Bird::update(float speed)
{
	getSprite().move(0.0f, -speed);
}