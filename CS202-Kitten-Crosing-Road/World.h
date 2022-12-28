#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <queue>
using namespace sf;
using namespace std;

#include "Object.h"
#include "Lane.h"

class World : public ListTextures
{
public:
	explicit						World(RenderWindow& window);
									~World();
	void							draw();
	bool							handleEvent(RenderWindow& window, View &mView);
	void							processEvent(System& gameSystem, Player& mPlayer);
	bool							worldRestart();
private: 
	int								getPosition(int laneIndex);
	int								generateNextLaneIndex(int status = 0);
	vector<Object>&					generate(vector<Object>& res, vector<Texture>& texture, int unit, int pos);
	void							drawElement(vector<Object>& target);
	void							drawListElements(vector<vector<Object>>& target);
	void							drawListElements(queue<vector<Object>> target);

private:

	int								nLane = 0;
	queue<vector<Object>>			mapBackground;
	vector<Lane*>					mLane;
	vector<int>						mapIndex; //
	const int						range = 32;
	RenderWindow& window;
	
	int								curID = 0;
};