#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Object.h"

using namespace sf;
using namespace std;

class Vehicle: public Object
{
public:
	Vehicle(RenderWindow& window, Texture& texture, int x_coor, int y_coor);

	void draw();
	void move();
private:
	Vector2f coord; // coordinate of vehicle
	float velo; // velocity of vehicle
	float acce; // acceleration of vehicle
	Time startMoveTime;
};