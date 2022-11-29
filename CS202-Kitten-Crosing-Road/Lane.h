#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "Object.h"
#include "Vehicle.h"
#include "Light.h"
#include "Player.h"

class Lane
{
public:
	Lane()
	{

	}
private:
};

class Road : public Lane
{
public:
	Road(RenderWindow& window, int dir, Texture& texture, int x_coor, int y_coor, int unit);

	void addLight(RenderWindow& window, vector<Texture>& texture, int x_coor, int y_coor, int unit);

	void draw();

	bool isCollided(Player mPlayer);
private:
	int dir; // 0: left to right, 1: right to left
	vector<Vehicle*>	listVehicle;
	vector<Light>		listLight;
};