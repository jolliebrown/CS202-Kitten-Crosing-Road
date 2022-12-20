#include "Lane.h"

Road::Road(RenderWindow& window, int dir, Texture& texture, int x_coor, int y_coor, int unit)
{
	this->dir = dir;
	Vehicle* Tem = new Vehicle(window, texture, x_coor, y_coor, dir, unit);
	listVehicle.push_back(Tem);
}

Road::Road(RenderWindow& window, int dir, Texture& texture, int x_coor, int y_coor, int unit, float initVelo, float limVelo)
{
	this->dir = dir;
	Vehicle* Tem = new Vehicle(initVelo, limVelo, window, texture, x_coor, y_coor, dir, unit);
	listVehicle.push_back(Tem);
}

Road::Road(const Road& road)
{
	cerr << "Deep copy...\n";
	dir = road.dir;
	for (auto v : road.listVehicle) {
		Vehicle* Tem = new Vehicle(*v);
		listVehicle.push_back(Tem);
	}
	/*for (auto v : road.listLight) {
		listLight.push_back(v);
	}*/
}

void Road::addLight(RenderWindow& window, vector<Texture>& texture, int x_coor, int y_coor, int unit)
{
	listLight.push_back(Light(window, texture, x_coor, y_coor, unit));
}

void Road::draw()
{
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