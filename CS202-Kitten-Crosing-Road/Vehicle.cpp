#include "Vehicle.h"

int Rand(int l, int r)
{
	int t = RAND_MAX;
	return l + (rand() * t + rand() * t + rand()) % (r - l + 1);
}

// Constructor
Vehicle::Vehicle(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit) : Object(window, texture, x_coor, y_coor, unit)
{
	limVelo = 0.2;
	initVelo = 0.1;
	velo = initVelo;
	acce = 0.0001;
	clock.restart();
	startMoveTime = milliseconds(Rand(1000, 8000));
	coord = Vector2f(x_coor, (float)(y_coor + (18 - Object::asset.getGlobalBounds().height) * 1.0 / 2));
	Object::asset.setPosition(coord);
}

Vehicle::Vehicle(float initVelo, float limVelo, RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit) : Object(window, texture, x_coor, y_coor, unit)
{
	this->limVelo = limVelo;
	this->initVelo = initVelo;
	velo = initVelo;
	acce = 0.0001;
	clock.restart();
	startMoveTime = milliseconds(Rand(1000, 8000));
	coord = Vector2f(x_coor, (float)(y_coor + (18 - Object::asset.getGlobalBounds().height) * 1.0 / 2));
	Object::asset.setPosition(coord);
}

void Vehicle::draw(int state, float x_coord)
{
	Object::draw();
	move(state, x_coord);
}

void Vehicle::accelerate()
{
	velo += acce;
	velo = min(velo, limVelo);
}

void Vehicle::move(int state, float x_coord)
{
	if (clock.getElapsedTime().asMilliseconds() < startMoveTime.asMilliseconds()) return;
	Object::asset.move(Vector2f(velo, 0));
	checkLight(state, x_coord);
	if (Object::asset.getPosition().x > BaseUnit * 14) {
		Object::asset.setPosition(-Object::asset.getGlobalBounds().width, coord.y);
		clock.restart();
		startMoveTime = milliseconds(Rand(1000, 8000));
		velo = initVelo;
	}
}

void Vehicle::checkLight(int state, float x_coord)
{
	float x_car = Object::asset.getGlobalBounds().width + Object::asset.getPosition().x;
	if (state == 0 || state == 1 && x_car > x_coord) {
		accelerate();
		return;
	}
	velo = min(velo, x_coord - x_car);
}

Ambulance::Ambulance(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit) : Vehicle(0.2, 0.25, window, texture, x_coor, y_coor, unit)
{

}

Ambulance::Ambulance(float initVelo, float limVelo, RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit) : Vehicle(initVelo, limVelo, window, texture, x_coor, y_coor, unit)
{

}

void Ambulance::checkLight(int state, float x_coord)
{
	Vehicle::accelerate();
}