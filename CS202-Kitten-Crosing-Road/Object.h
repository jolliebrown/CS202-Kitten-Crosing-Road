#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace sf;
using namespace std;

// store all textures that need to be loaded
class ListTextures
{
public:
	ListTextures();
private: 
	vector<Texture>&		load(vector<Texture>& scr, string fileName, int x_coor, int y_coor, int width, int height, int unit);
protected:
	vector<Texture>			grass;
	vector<Texture>			road;
	vector<vector<Texture>> user;
};


// dung cho 1 cai tile nao do (vi du: background, car, user, ...)
class Object
{
public:
	Object(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit);
	Object(const Object& scr);
	//Object&					operator=(const Object& scr);
	void					draw();
private:
	Sprite					asset;
	Texture&				mAsset;
	FloatRect				bound;
	int						unit;
	RenderWindow&			window;
};