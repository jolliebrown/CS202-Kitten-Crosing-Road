#include "Lane.h"

Lane::Lane()
{

}

Road::Road()
{
	dir = 0;
	y_coor = 0;
	unit = 0;
}

Road::Road(RenderWindow& window, int x_coor, int y_coor, int unit, vector<Texture>& mTexture) :
	window(&window)
{
	this->dir = dir;
	this->y_coor = y_coor;
	this->unit = unit;
	this->mTexture = mTexture;
	generate(window, listTexture, mTexture, unit, y_coor);
}

Road::Road(RenderWindow& window, int dir, Texture& texture, int x_coor, int y_coor, int unit, vector<Texture>& mTexture):
	window(&window)
{
	this->dir = dir;
	this->y_coor = y_coor;
	this->unit = unit;
	this->mTexture = mTexture;
	for (int i = 0; i < 1; ++i) {
		Vehicle* Tem = new Vehicle(window, texture, x_coor, y_coor, dir, unit);
		listVehicle.push_back(Tem);
	}
	generate(window, listTexture, mTexture, unit, y_coor);
}

Road::Road(RenderWindow& window, int dir, int numLight, vector<Texture>& listLightTexture, Texture& texture, int x_coor, int y_coor, int unit, vector<Texture>& mTexture) :
	window(&window)
{
	this->dir = dir;
	this->y_coor = y_coor;
	this->unit = unit;
	this->mTexture = mTexture;
	for (int i = 0; i < 1; ++i) {
		Vehicle* Tem = new Vehicle(window, texture, x_coor, y_coor, dir, unit);
		listVehicle.push_back(Tem);
	}
	generate(window, listTexture, mTexture, unit, y_coor);
	addLight(window, listLightTexture, BaseUnit * 3, y_coor, unit);
	addLight(window, listLightTexture, BaseUnit * 10, y_coor, unit);
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
	listTexture = road.listTexture;
	//generate(*window, listTexture, mTexture, unit, y_coor);
	listLight = road.listLight;
}

Road& Road::operator = (const Road& road)
{
	//cerr << "Assignment...\n";
	if (this == &road) return *this;
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
	listLight = road.listLight;
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
	listLight.push_back(Light(window, texture, x_coor, y_coor - 5, unit));
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
		/*if (listLight.size() == 0) car->move(0, 0);
		else {
			car->move(listLight[0].getState(), listLight[0].getPos());
		}*/
		int low = 0, high = (int)listLight.size() - 1, pos = -1;
		while (low <= high) {
			int mid = (low + high) / 2;
			if (car->isPass(listLight[mid].getState(), listLight[mid].getPos())) {
				if (car->getDir() == 1) low = mid + 1;
				else high = mid - 1;
			}
			else {
				pos = mid;
				if (car->getDir() == 1) high = mid - 1;
				else low = mid + 1;
			}
		}
		if (pos == -1) car->move(0, 0);
		else car->move(listLight[pos].getState(), listLight[pos].getPos());
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

/// ******************* RailWay ******************* ///

RailWay::RailWay()
{
	dir = 0;
	y_coor = 0;
	unit = 0;
}

RailWay::RailWay(RenderWindow& window, int x_coor, int y_coor, int unit, vector<Texture>& mTexture) :
	window(&window)
{
	this->dir = dir;
	this->y_coor = y_coor;
	this->unit = unit;
	this->mTexture = mTexture;
	generate(window, listTexture, mTexture, unit, y_coor);
}

RailWay::RailWay(RenderWindow& window, int dir, Texture& texture, int x_coor, int y_coor, int unit, vector<Texture>& mTexture) :
	window(&window)
{
	this->dir = dir;
	this->y_coor = y_coor;
	this->unit = unit;
	this->mTexture = mTexture;
	for (int i = 0; i < 1; ++i) {
		Vehicle* Tem = new Vehicle(window, texture, x_coor, y_coor, dir, unit);
		listVehicle.push_back(Tem);
	}
	generate(window, listTexture, mTexture, unit, y_coor);
}

RailWay::RailWay(RenderWindow& window, int dir, int numLight, vector<Texture>& listLightTexture, Texture& texture, int x_coor, int y_coor, int unit, vector<Texture>& mTexture) :
	window(&window)
{
	this->dir = dir;
	this->y_coor = y_coor;
	this->unit = unit;
	this->mTexture = mTexture;
	for (int i = 0; i < 1; ++i) {
		Vehicle* Tem = new Vehicle(0.12, 0.2, window, texture, x_coor, y_coor, dir, unit);
		listVehicle.push_back(Tem);
	}
	generate(window, listTexture, mTexture, unit, y_coor);
}

RailWay::RailWay(const RailWay& railway) :
	window(railway.window)
{
	//cerr << "Deep copy...\n";
	dir = railway.dir;
	y_coor = railway.y_coor;
	unit = railway.unit;
	mTexture = railway.mTexture;

	for (auto v : railway.listVehicle) {
		Vehicle* Tem = new Vehicle(*v);
		listVehicle.push_back(Tem);
	}
	listTexture = railway.listTexture;
	//generate(*window, listTexture, mTexture, unit, y_coor);
	listLight = railway.listLight;
}

vector<Object>& RailWay::generate(RenderWindow& window, vector<Object>& res, vector<Texture>& texture, int unit, int pos)
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

void RailWay::addLight(RenderWindow& window, vector<Texture>& texture, int x_coor, int y_coor, int unit)
{
	listLight.push_back(Light(window, texture, x_coor, y_coor - 5, unit));
}

void RailWay::draw()
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

void RailWay::handleEvent() {
	//return;
	for (auto& car : listVehicle) {
		/*if (listLight.size() == 0) car->move(0, 0);
		else {
			car->move(listLight[0].getState(), listLight[0].getPos());
		}*/
		int low = 0, high = (int)listLight.size() - 1, pos = -1;
		while (low <= high) {
			int mid = (low + high) / 2;
			if (car->isPass(listLight[mid].getState(), listLight[mid].getPos())) {
				if (car->getDir() == 1) low = mid + 1;
				else high = mid - 1;
			}
			else {
				pos = mid;
				if (car->getDir() == 1) high = mid - 1;
				else low = mid + 1;
			}
		}
		if (pos == -1) car->move(0, 0);
		else car->move(listLight[pos].getState(), listLight[pos].getPos());
	}
	for (auto& light : listLight) light.move();
}

bool RailWay::isCollided(Player& mPlayer)
{
	for (auto& car : listVehicle) if (mPlayer.isCollided(*car)) return true;
	return false;
}

int RailWay::getPosition() {
	return y_coor;
}