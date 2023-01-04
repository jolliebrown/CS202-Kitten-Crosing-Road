#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "Object.h"

using namespace sf;
using namespace std;

class Vehicle: public Object
{
public:
	Vehicle(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit);

	virtual void				draw(int state = 0, float x_coord = 0) = 0;
	virtual bool				move(int state, float x_coord) = 0;
	virtual void				accelerate() = 0;
	virtual void				checkLight(int state, float x_coord) = 0;
	virtual bool				isPass(int state, float x_coord) = 0;
	virtual int					getDir() = 0;
	virtual float				getPosLow() = 0;
	virtual float				getPosHigh() = 0;
	virtual void				restartClock() = 0;
private:
protected:
	SoundBuffer					buffer;
	Sound						sound;
};

class Car : public Vehicle
{
public:
	Car(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit);
	Car(float initVelo, float limVelo, RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit);
	Car(Time moveTime, float initVelo, float limVelo, RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit);
	Car(const Car& car);

	void						draw(int state = 0, float x_coord = 0);
	bool						move(int state, float x_coord);
	void						accelerate();
	void						checkLight(int state, float x_coord);
	bool						isPass(int state, float x_coord);
	int							getDir();
	float						getPosLow();
	float						getPosHigh();
	void						restartClock();
private:
	Vector2f					coord; // coordinate of vehicle
	float						startPoint;
	float						endPoint;
	float						velo; // velocity of vehicle
	float						limVelo; // limit velocity of vehicle
	float						initVelo; // initial velocity of vehicle
	float						acce; // acceleration of vehicle
	Time						startMoveTime;
	Clock						clock;
	int							dir;
};

class Animal : public Vehicle
{
public:
	Animal(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit);
	Animal(float initVelo, float limVelo, RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit);
	Animal(Time moveTime, float initVelo, float limVelo, RenderWindow& window, vector<Texture>& texture, int x_coor, int y_coor, int _dir, int unit);
	Animal(const Animal& animal);

	void						draw(int state = 0, float x_coord = 0);
	bool						move(int state, float x_coord);
	void						accelerate();
	void						checkLight(int state, float x_coord);
	bool						isPass(int state, float x_coord);
	int							getDir();
	float						getPosLow();
	float						getPosHigh();
	void						restartClock();
private:
	Vector2f					coord; // coordinate of vehicle
	float						startPoint;
	float						endPoint;
	float						velo; // velocity of vehicle
	float						limVelo; // limit velocity of vehicle
	float						initVelo; // initial velocity of vehicle
	float						acce; // acceleration of vehicle
	Time						startMoveTime;
	Clock						clock;
	int							dir;
	int							curView;
	vector<Texture>				listTexture;
};

class Train : public Vehicle
{
public:
	Train(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit);
	Train(float initVelo, float limVelo, RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit);
	Train(const Train& train);

	void						draw(int state = 0, float x_coord = 0);
	bool						move(int state, float x_coord);
	void						accelerate();
	void						checkLight(int state, float x_coord);
	bool						isPass(int state, float x_coord);
	int							getDir();
	float						getPosLow();
	float						getPosHigh();
	void						restartClock();
private:
	Vector2f					coord; // coordinate of vehicle
	float						startPoint;
	float						endPoint;
	float						velo; // velocity of vehicle
	float						limVelo; // limit velocity of vehicle
	float						initVelo; // initial velocity of vehicle
	float						acce; // acceleration of vehicle
	Time						startMoveTime;
	Clock						clock;
	int							dir;
};

class Wood : public Vehicle
{
public:
	Wood(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit);
	Wood(float initVelo, float limVelo, RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit);
	Wood(Time moveTime, float initVelo, float limVelo, RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit);
	Wood(const Wood& car);

	void						draw(int state = 0, float x_coord = 0);
	bool						move(int state, float x_coord);
	void						accelerate();
	void						checkLight(int state, float x_coord);
	bool						isPass(int state, float x_coord);
	int							getDir();
	float						getPosLow();
	float						getPosHigh();
	void						restartClock();
private:
	Vector2f					coord; // coordinate of vehicle
	float						startPoint;
	float						endPoint;
	float						velo; // velocity of vehicle
	float						limVelo; // limit velocity of vehicle
	float						initVelo; // initial velocity of vehicle
	float						acce; // acceleration of vehicle
	Time						startMoveTime;
	Clock						clock;
	int							dir;
};