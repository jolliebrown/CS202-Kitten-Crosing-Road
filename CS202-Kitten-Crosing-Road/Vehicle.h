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
						Vehicle(float initVelo, float limVelo, RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit);

	void				draw(int state, float x_coord);
	void				move(int state, float x_coord);
	void				accelerate();
	virtual void		checkLight(int state, float x_coord);
private:
	Vector2f			coord; // coordinate of vehicle
	float				velo; // velocity of vehicle
	float				limVelo; // limit velocity of vehicle
	float				initVelo; // initial velocity of vehicle
	float				acce; // acceleration of vehicle
	Time				startMoveTime;
	Clock				clock;
};

class Ambulance : public Vehicle
{
public:
						Ambulance(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit);
						Ambulance(float initVelo, float limVelo, RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit);
	void				checkLight(int state, float x_coord);
private:

};