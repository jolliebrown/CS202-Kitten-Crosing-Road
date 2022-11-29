#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>

const int BaseUnit = 16;
const int TimeMove = 361;

using namespace sf;
using namespace std;

// store all textures that need to be loaded
class ListTextures
{
public:
							ListTextures();
private: 
	vector<Texture>&		load(vector<Texture>& scr, string fileName, int x_coor, int y_coor, int width, int height, int unit);
	vector<Texture>&		onePicLoad(vector<Texture>& scr, string fileName);
	vector<Texture>&		onePicLoad(vector<Texture>& scr, string fileName, int x_coor, int y_coor, int width, int height);
protected:
	vector<Texture>			grass;
	vector<Texture>			road;
	vector<Texture>			rail;
public:
	vector<Texture>			car;
	vector<Texture>			user;
	vector<Texture>			light;
};


// dung cho 1 cai tile nao do (vi du: background, car, user, ...)
class Object
{
public:
	Object(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit);
	Object(RenderWindow& window, Texture& texture, int x_coor, int y_coor);
							Object(const Object& scr);
	//Object&					operator=(const Object& scr);
	void					draw();
	bool isCollided(const Object& src);
	FloatRect				getBound();
	const FloatRect			getBound() const;
private:
	RenderWindow&			window;
	Texture&				mAsset;
protected:
	int						unit;
	Sprite					asset;
	
};