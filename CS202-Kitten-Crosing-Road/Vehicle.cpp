#include "Vehicle.h"

int Rand(int l, int r)
{
	int t = RAND_MAX;
	return l + (rand() * t + rand() * t + rand()) % (r - l + 1);
}

// Constructor

Vehicle::Vehicle(RenderWindow& window, Texture& texture, int x_coor, int y_coor): Object(window, texture, x_coor, y_coor)
{

	velo = 0.1;
	acce = 0.1;
	startMoveTime = milliseconds(Rand(2000, 10000));
	coord = Vector2f(x_coor, y_coor);

	/*sprVehicle.setTexture(txrVehicle);
	sprVehicle.setTextureRect(IntRect(0, 0, txrVehicle.getSize().x, 35));

	coord = Vector2f(-sprVehicle.getGlobalBounds().width, lane * ROAD_HEIGHT + ROAD_HEIGHT / 2 - sprVehicle.getGlobalBounds().height / 2);

	sprVehicle.setPosition(coord);*/
}

void Vehicle::draw()
{
	Object::draw();
	move();
}

void Vehicle::move()
{
	Object::asset.move(Vector2f(velo, 0));
	if (Object::asset.getPosition().x > BaseUnit * 14) {
		Object::asset.setPosition(-Object::asset.getGlobalBounds().width, Object::asset.getPosition().y);
	}
}