#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "Object.h"

using namespace sf;
using namespace std;

class Vehicle: public Object
{
public:
						Vehicle() = default;
						Vehicle(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit);

	void				draw(int state, float x_coord);
	void				move(int state, float x_coord);
	void				checkLight(int state, float x_coord);
	void				draw();
	void				move();
private:
	Vector2f			coord; // coordinate of vehicle
	float				velo; // velocity of vehicle
	float				acce; // acceleration of vehicle
	Time				startMoveTime;
	Clock				clock;
};