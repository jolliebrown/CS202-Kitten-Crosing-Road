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
	Lane();

	//virtual Lane&				operator = (const Lane& road) = 0;
	virtual vector<Object>&		generate(RenderWindow& window, vector<Object>& res, vector<Texture>& texture, int unit, int pos) = 0;
	virtual void				addLight(RenderWindow& window, vector<Texture>& texture, int x_coor, int y_coor, int unit) = 0;
	//virtual bool				insideView() = 0;
	virtual void				draw() = 0;
	virtual void				handleEvent() = 0;
	virtual bool				isCollided(Player& mPlayer) = 0;
	virtual int					getPosition() = 0;
private:
};

class Road: public Lane
{
public:
	Road();
	Road(RenderWindow& window, int x_coor, int y_coor, int unit, vector<Texture>& mTexture);
	Road(RenderWindow& window, int dir, Texture& texture, int x_coor, int y_coor, int unit, vector<Texture>& mTexture);
	Road(RenderWindow& window, int dir, int numLight, vector<Texture>& listLightTexture, Texture& texture, int x_coor, int y_coor, int unit, vector<Texture>& mTexture);
	Road(RenderWindow& window, int dir, Texture& texture, int x_coor, int y_coor, int unit, float initVelo, float limVelo, vector<Texture>& mTexture);
	Road(const Road& road);

	Road&						operator = (const Road& road);
	vector<Object>&				generate(RenderWindow& window, vector<Object>& res, vector<Texture>& texture, int unit, int pos);
	void						addLight(RenderWindow& window, vector<Texture>& texture, int x_coor, int y_coor, int unit);
	//bool						insideView();
	void						draw();
	void						handleEvent();
	bool						isCollided(Player& mPlayer);
	int							getPosition();
private:
	int							dir; // 0: left to right, 1: right to left
	int							y_coor;
	int							unit;
	RenderWindow*				window;
	vector<Texture>				mTexture;
	vector<Vehicle*>			listVehicle;
	vector<Light>				listLight;
	vector<Object>				listTexture;
	const int					range = 32;
};

class RailWay: public Lane
{
public:
	RailWay();
	RailWay(RenderWindow& window, int x_coor, int y_coor, int unit, vector<Texture>& mTexture);
	RailWay(RenderWindow& window, int dir, Texture& texture, int x_coor, int y_coor, int unit, vector<Texture>& mTexture);
	RailWay(RenderWindow& window, int dir, int numLight, vector<Texture>& listLightTexture, Texture& texture, int x_coor, int y_coor, int unit, vector<Texture>& mTexture);
	RailWay(RenderWindow& window, int dir, Texture& texture, int x_coor, int y_coor, int unit, float initVelo, float limVelo, vector<Texture>& mTexture);
	RailWay(const RailWay& railway);

	vector<Object>&				generate(RenderWindow& window, vector<Object>& res, vector<Texture>& texture, int unit, int pos);
	void						addLight(RenderWindow& window, vector<Texture>& texture, int x_coor, int y_coor, int unit);
	//bool						insideView();
	void						draw();
	void						handleEvent();
	bool						isCollided(Player& mPlayer);
	int							getPosition();
private:
	int							dir; // 0: left to right, 1: right to left
	int							y_coor;
	int							unit;
	RenderWindow*				window;
	vector<Texture>				mTexture;
	vector<Vehicle*>			listVehicle;
	vector<Light>				listLight;
	vector<Object>				listTexture;
	const int					range = 32;
};