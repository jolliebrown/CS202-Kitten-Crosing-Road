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

void Obstacle::saveMap(ofstream& os) {
	int x_coor = Object::asset.getPosition().x;
	int y_coor = Object::asset.getPosition().y;
	os << x_coor << " " << y_coor << "\n";
}


int Obstacle::getState()
{
	return state;
}

float Obstacle::getPos()
{
	return Object::asset.getPosition().x;
}