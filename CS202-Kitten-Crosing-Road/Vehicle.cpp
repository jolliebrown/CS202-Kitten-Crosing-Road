#include "Vehicle.h"

int Rand(int l, int r)
{
	int t = RAND_MAX;
	return l + (rand() * t + rand() * t + rand()) % (r - l + 1);
}

// Constructor
Vehicle::Vehicle(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit): Object(window, texture, x_coor, y_coor, unit)
{
	velo = 0.1;
	acce = 0.02;
	clock.restart();
	startMoveTime = milliseconds(Rand(1000, 8000));
	coord = Vector2f(x_coor, (float) (y_coor + (18 - Object::asset.getGlobalBounds().height) * 1.0 / 2));
	Object::asset.setPosition(coord);
}

void Vehicle::draw()
{
	Object::draw();
	move();
}

void Vehicle::move()
{
	if (clock.getElapsedTime().asMilliseconds() < startMoveTime.asMilliseconds()) return;
	Object::asset.move(Vector2f(velo, 0));
	if (Object::asset.getPosition().x > BaseUnit * 14) {
		Object::asset.setPosition(-Object::asset.getGlobalBounds().width, coord.y);
		clock.restart();
		startMoveTime = milliseconds(Rand(1000, 8000));
		velo += acce;
	}
}