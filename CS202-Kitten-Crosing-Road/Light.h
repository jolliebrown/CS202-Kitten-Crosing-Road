#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Object.h"

using namespace sf;
using namespace std;

class Light: public Object
{
public:
						Light(int state, RenderWindow& window, vector<Texture>& texture, int x_coor, int y_coor, int unit);

	void				draw();
private:
	int					state; // 0: green, 1: yellow, 2: red
	Time				count[3];
	Clock				clock;
	vector<Texture>		listLight;
};