#include "Vehicle.h"

int Rand(int l, int r)
{
	int t = RAND_MAX;
	return l + (rand() * t + rand() * t + rand()) % (r - l + 1);
}

// Constructor
Vehicle::Vehicle(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit) : 
	Object(window, texture, x_coor, y_coor, unit)
{
	dir = _dir; limVelo = dir * 0.2; initVelo = dir * 0.1; velo = dir * initVelo; acce = dir * 0.01;

	startPoint = (dir == 1) ? -Object::asset.getGlobalBounds().width : BaseUnit * 29 + Object::asset.getGlobalBounds().width;
	endPoint = (dir == 1) ? BaseUnit * 29 + Object::asset.getGlobalBounds().width : -Object::asset.getGlobalBounds().width;

	Object::asset.setOrigin(Object::asset.getGlobalBounds().width / 2, Object::asset.getGlobalBounds().height / 2);
	if (dir == -1) Object::asset.rotate(180);

	clock.restart();
	startMoveTime = milliseconds(Rand(1000, 8000));
	coord = Vector2f(x_coor, (float)(y_coor + 16 / 2));
	Object::asset.setPosition(startPoint, coord.y);
}

Vehicle::Vehicle(float initVelo, float limVelo, RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit) : 
	Object(window, texture, x_coor, y_coor, unit)
{
	dir = _dir; this->limVelo = dir * limVelo; this->initVelo = dir * initVelo; velo = dir * initVelo; acce = dir * 0.01;

	startPoint = (dir == 1) ? -Object::asset.getGlobalBounds().width : BaseUnit * 29 + Object::asset.getGlobalBounds().width;
	endPoint = (dir == 1) ? BaseUnit * 29 + Object::asset.getGlobalBounds().width : -Object::asset.getGlobalBounds().width;

	Object::asset.setOrigin(Object::asset.getGlobalBounds().width / 2, Object::asset.getGlobalBounds().height / 2);
	if (dir == -1) Object::asset.rotate(180);

	clock.restart();
	startMoveTime = milliseconds(Rand(1000, 8000));
	coord = Vector2f(x_coor, (float)(y_coor + 16 / 2));
	Object::asset.setPosition(startPoint, coord.y);
}

void Vehicle::draw(int state, float x_coord)
{
	Object::draw();
	/*move(state, x_coord);*/
}

void Vehicle::accelerate()
{
	velo += acce;
	if ((velo > limVelo) == (dir == 1)) velo = limVelo;
}

void Vehicle::move(int state, float x_coord)
{
	if (clock.getElapsedTime().asMilliseconds() < startMoveTime.asMilliseconds()) return;
	Object::asset.move(Vector2f(velo, 0));
	checkLight(state, x_coord);
	if ((Object::asset.getPosition().x > endPoint) == (dir == 1)) {
		Object::asset.setPosition(startPoint, coord.y);
		clock.restart();
		startMoveTime = milliseconds(Rand(1000, 8000));
		velo = initVelo;
	}
}

void Vehicle::checkLight(int state, float x_coord)
{
	float x_car = Object::asset.getGlobalBounds().width + Object::asset.getPosition().x;
	if (state == 0 || x_car > x_coord) {
		accelerate();
		return;
	}
	velo = min(velo, x_coord - x_car);
}