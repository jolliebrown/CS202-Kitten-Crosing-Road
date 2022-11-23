#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>


#include "World.h"
#include "Player.h"
#include "Vehicle.h"
#include "Light.h"


using namespace sf;
using namespace std;

class Game
{
public:
	Game(vector<int>& mapIndex);
	void					run();


private:
	void					processEvents();
	void					update(Time elapsedTime);
	void					render();
	void					updateStatistics(Time elapsedTime);

private:
	static const Time		TimePerFrame;
	RenderWindow			mWindow;
	View					mView;
	Text					mStatisticsText;
	Time					mStatisticsUpdateTime;
	std::size_t				mStatisticsNumFrames;

	// backdround demo
	vector<int>				mapIndex;
	World					mWorld;
	Player					mPlayer, secPlayer;
	vector<Vehicle>			mCar;
	Light					mLight;
	// 1 for road, 0 for land
};