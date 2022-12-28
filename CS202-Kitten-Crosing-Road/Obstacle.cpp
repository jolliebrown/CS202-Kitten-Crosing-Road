#include "Obstacle.h"

Obstacle::Obstacle(RenderWindow& window, vector<Texture>& texture, int x_coord, int y_coord, int unit) : Object(window, texture[0], x_coord, y_coord, unit)
{
	this->state = 0;
	listObstacle = texture;
}

Obstacle::Obstacle(int state, RenderWindow& window, vector<Texture>& texture, int x_coord, int y_coord, int unit) : Object(window, texture[0], x_coord, y_coord, unit)
{
	this->state = state;
	listObstacle = texture;
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