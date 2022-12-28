#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Object.h"

using namespace sf;
using namespace std;

class Obstacle : public Object
{
public:
	Obstacle(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit);
	Obstacle(int state, RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit);
	//Obstacle(const Obstacle& Obstacle);

	void				draw();
	void				move();
	float				getPos();
	int					getState();
private:
	int					state; // 0: exist, 1: destroyed
	vector<Texture>		listObstacle;
};