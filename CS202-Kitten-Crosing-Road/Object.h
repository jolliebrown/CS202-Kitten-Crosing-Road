#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>




using namespace sf;
using namespace std;

class ListTextures
{
public:
	ListTextures();
private: 
	vector<Texture>& load(string fileName, int x_coor, int y_coor, int width, int height, int unit);
protected:
	vector<Texture> grass;
	vector<Texture> road;
	vector<vector<Texture>> user;
};


class Object
{
public:
	Object(RenderWindow& window, Texture& texture, int x_coor, int y_coor);
	void					draw();
private:
	Sprite					asset;
	Texture&				mAsset;
	FloatRect				bound;
	RenderWindow& window;
};