#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>


#include "World.h"
#include "Player.h"
#include "Vehicle.h"
#include "Light.h"
#include "Lane.h"
#include "System.h"
#include "Menu.h"

using namespace sf;
using namespace std;

class Game
{
public:
							Game();
							~Game();
	void					run();
	bool					gameContinue();
	bool					gameRestart();
private:
	void					processEvents();
	void					update(Time elapsedTime);
	void					render();
	void					updateStatistics(Time elapsedTime);
	void					viewScroll(View &mView, Player& mPlayer);
	void					setCur(const Event& event);
	void					saveFile();
private:
	System					gameSystem;
	static const Time		TimePerFrame;
	RenderWindow			mWindow;
	View					mView;
	Text					mStatisticsText;
	Time					mStatisticsUpdateTime;
	std::size_t				mStatisticsNumFrames;
	Vector2f				mouse;
	Cursor					cursor;
	Image					cur_img, cur_clicked;


	// backdround demo
	vector<int>				mapIndex;
	World					mWorld;
	Player					mPlayer;

	Vector2f				viewPosition;
	// 1 for road, 0 for land

	vector<Scene*>			scene;
};