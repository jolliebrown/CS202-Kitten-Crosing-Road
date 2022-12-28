#include "Obstacle.h"

Obstacle::Obstacle(RenderWindow& window, Texture& texture, int x_coord, int y_coord, int unit) : Object(window, texture, x_coord, y_coord, unit)
{
	this->state = 0;
}

Obstacle::Obstacle(int state, RenderWindow& window, Texture& texture, int x_coord, int y_coord, int unit) : Object(window, texture, x_coord, y_coord, unit)
{
	this->state = state;
}

void Obstacle::draw()
{
	Object::draw();
}



int Obstacle::getState()
{
	return state;
}

float Obstacle::getPos()
{
	return Object::asset.getPosition().x;
}