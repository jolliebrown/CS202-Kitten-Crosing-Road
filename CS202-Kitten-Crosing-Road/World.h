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
class Lane;
class Player;
class World : public ListTextures
{
public:
	bool							isColliedObstacle(Player& mPlayer, int deltaX, int deltaY);
	void							resetVehicle();
	explicit						World(RenderWindow& window);
	explicit						World(RenderWindow& window, bool check);
									~World();
	void							writeFile(ofstream& fout);
	void							draw(bool onlyLane = false);
	bool							handleEvent(RenderWindow& window, View &mView);
	void							processEvent(System& gameSystem, Player& mPlayer);
	bool							worldRestart();
	void							saveMap(ofstream &os) ;
private: 
	
	int								getPosition(int laneIndex);
	int								generateNextLaneIndex(int status = 0);
	vector<Object>&					generate(vector<Object>& res, vector<Texture>& texture, int unit, int pos);
private:

	int								nLane = 0;
	queue<vector<Object>>			mapBackground;
	vector<Lane*>					mLane;
	vector<int>						mapIndex; //
	const int						range = 32;
	RenderWindow& window;
	
	int								curID = 0;
};