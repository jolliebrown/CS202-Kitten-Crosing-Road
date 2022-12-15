#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "Object.h"
#include "Vehicle.h"
#include "Light.h"
#include "Player.h"

class Road
{
public:
	Road(RenderWindow& window, int dir, Texture& texture, int x_coor, int y_coor, int unit);
	Road(RenderWindow& window, int dir, Texture& texture, int x_coor, int y_coor, int unit, float initVelo, float limVelo);

	void addLight(RenderWindow& window, vector<Texture>& texture, int x_coor, int y_coor, int unit);

	void draw();
	void handleEvent();
	bool isCollided(Player mPlayer);
private:
	int dir; // 0: left to right, 1: right to left
	vector<Vehicle*>	listVehicle;
	vector<Light>		listLight;
};

class RailWay
{
public:
	RailWay()
	{

	}
private:
};