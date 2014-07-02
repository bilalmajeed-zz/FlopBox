#include "Bird.h"
#include <assert.h>

Bird::Bird()
{
	load("res/graphics.png");
	assert(loaded());
}

void Bird::update()
{
}