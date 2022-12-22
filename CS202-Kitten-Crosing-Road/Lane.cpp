#include "Lane.h"

Road::Road(RenderWindow& window, int x_coor, int y_coor, int unit, vector<Texture> mTexture) :
	window(&window)
{
	this->dir = dir;
	this->y_coor = y_coor;
	this->unit = unit;
	this->mTexture = mTexture;
	generate(window, listTexture, mTexture, unit, y_coor);
}

Road::Road(RenderWindow& window, int dir, Texture& texture, int x_coor, int y_coor, int unit, vector<Texture> mTexture):
	window(&window)
{
	this->dir = dir;
	this->y_coor = y_coor;
	this->unit = unit;
	this->mTexture = mTexture;
	Vehicle* Tem = new Vehicle(window, texture, x_coor, y_coor, dir, unit);
	listVehicle.push_back(Tem);
	generate(window, listTexture, mTexture, unit, y_coor);
}

Road::Road(RenderWindow& window, int dir, Texture& texture, int x_coor, int y_coor, int unit, float initVelo, float limVelo, vector<Texture> mTexture):
	window(&window)
{
	this->dir = dir;
	this->y_coor = y_coor;
	this->unit = unit;
	this->mTexture = mTexture;
	Vehicle* Tem = new Vehicle(initVelo, limVelo, window, texture, x_coor, y_coor, dir, unit);
	listVehicle.push_back(Tem);
	generate(window, listTexture, mTexture, unit, y_coor);
}

Road::Road(const Road& road):
	window(road.window)
{
	//cerr << "Deep copy...\n";
	dir = road.dir;
	y_coor = road.y_coor;
	unit = road.unit;
	mTexture = road.mTexture;

	for (auto v : road.listVehicle) {
		Vehicle* Tem = new Vehicle(*v);
		listVehicle.push_back(Tem);
	}
	//listTexture = road.listTexture;
	generate(*window, listTexture, mTexture, unit, y_coor);
	/*for (auto v : road.listLight) {
		listLight.push_back(v);
	}*/
}

Road& Road::operator = (const Road& road)
{
	//cerr << "Assignment...\n";
	delete window;
	window = road.window;
	dir = road.dir;
	y_coor = road.y_coor;
	unit = road.unit;
	mTexture = road.mTexture;
	listVehicle.clear();
	for (auto v : road.listVehicle) {
		Vehicle* Tem = new Vehicle(*v);
		listVehicle.push_back(Tem);
	}
	listTexture = road.listTexture;
	//generate(*window, listTexture, mTexture, unit, y_coor);
	/*for (auto v : road.listLight) {
		listLight.push_back(v);
	}*/
	return *this;
}

vector<Object>& Road::generate(RenderWindow& window, vector<Object>& res, vector<Texture>& texture, int unit, int pos)
{
	res.clear();
	int countTextures = texture.size();
	for (int i = 0; i < range; i++)
	{
		int random = rand() % countTextures;
		Object tmp(window, texture[random], i * unit, pos, unit);
		res.push_back(tmp);
	}
	// TODO: insert return statement here
	return res;
}

void Road::addLight(RenderWindow& window, vector<Texture>& texture, int x_coor, int y_coor, int unit)
{
	listLight.push_back(Light(window, texture, x_coor, y_coor, unit));
}

void Road::draw()
{
	for (unsigned int i = 0; i < listTexture.size(); i++)
	{
		listTexture[i].draw();
	}
	for (auto& car : listVehicle) {
		if (listLight.size() == 0) car->draw();
		else car->draw(listLight[0].getState(), listLight[0].getPos());
	}
	for (auto& light : listLight) light.draw();
}

void Road::handleEvent() {
	//return;
	for (auto& car : listVehicle) {
		if (listLight.size() == 0) car->move(0, 0);
		else {
			car->move(listLight[0].getState(), listLight[0].getPos());
		}
	}
	for (auto& light : listLight) light.move();
}

bool Road::isCollided(Player& mPlayer)
{
	for (auto& car : listVehicle) if (mPlayer.isCollided(*car)) return true;
	return false;
}

int Road::getPosition() {
	return y_coor;
}