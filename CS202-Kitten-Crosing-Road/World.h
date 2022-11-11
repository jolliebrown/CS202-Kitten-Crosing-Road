#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
using namespace sf;
using namespace std;

#include "Object.h"

class World : public ListTextures
{
public:
	World(ifstream& fin, RenderWindow& window);
	World(RenderWindow& window);
	void					draw();
private:
	vector<Object>			grassBackground;
	vector<Object>			roadBackground;
	vector<int>				mapIndex; //
	RenderWindow& window;
};