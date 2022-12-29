#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Object.h"

using namespace sf;
using namespace std;

class Light: public Object
{
public:
						Light(RenderWindow& window, vector<Texture>& texture, int x_coor, int y_coor, int unit);
						Light(int state, RenderWindow& window, vector<Texture>& texture, int x_coor, int y_coor, int unit);
						Light(const Light& light);

	void				draw();
	void				move();
	float				getPos(int dir);
	int					getState();
	void				setState(int state);
private:
	int					state; // 0: green, 1: yellow, 2: red
	Time				count[3];
	Clock				clock;
	vector<Texture>		listLight;
};