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

void Road::addObstacle(RenderWindow& window, vector<Texture>& texture, int x_coor, int y_coor, int unit)
{
	int k = Rand(1, 100) % 2;
	listObstacle.push_back(Obstacle(window, texture[k], x_coor, y_coor - 5, unit));
}



Road::Road(RenderWindow& window, int x_coor, int y_coor, int unit, vector<Texture>& listTextureObstacle , vector<Texture>& mTexture) :
	window(&window)
{
	this->dir = dir;
	this->y_coor = y_coor;
	this->unit = unit;
	this->mTexture = mTexture;
	generate(window, listTexture, mTexture, unit, y_coor);
	addObstacle(window, listTextureObstacle, BaseUnit * (5 + Rand(1, 3)) , y_coor, unit);
	addObstacle(window, listTextureObstacle, BaseUnit * (10 + Rand(1, 3)), y_coor, unit);
	addObstacle(window, listTextureObstacle, BaseUnit * (15 + Rand(1, 3)), y_coor, unit);
}

Road::Road(RenderWindow& window, int dir, Texture& texture, int x_coor, int y_coor, int unit, vector<Texture>& mTexture):
	window(&window)
{
	this->dir = dir;
	this->y_coor = y_coor;
	this->unit = unit;
	this->mTexture = mTexture;
	for (int i = 0; i < 1; ++i) {
		Vehicle* Tem = new Car(window, texture, x_coor, y_coor, dir, unit);
		listVehicle.push_back(Tem);
	}
	generate(window, listTexture, mTexture, unit, y_coor);
}

Road::Road(RenderWindow& window, int dir, int numLight, vector<Texture>& listLightTexture, Texture& texture, int x_coor, int y_coor, int unit, vector<Texture>& mTexture, int level) :
	window(&window)
{
	this->dir = dir;
	this->y_coor = y_coor;
	this->unit = unit;
	this->mTexture = mTexture;
	int numCars = 1;
	if (level > 20) {
		numCars++;
	}
	if (level > 40) {
		numCars++;
	}
	if (level > 60) {
		numCars++;
	}
	float velo = 0.1;
	if (level > 30) velo = 0.15;
	if (level > 60) velo = 0.2;
	for (int i = 0; i < numCars; ++i) {
		Vehicle* Tem = new Car(velo, velo, window, texture, x_coor, y_coor, dir, unit);
		listVehicle.push_back(Tem);
	}
	generate(window, listTexture, mTexture, unit, y_coor);
	if (level > 20) {
		addLight(window, listLightTexture, BaseUnit * 5, y_coor, unit);
	}
	if (level > 40) {
		addLight(window, listLightTexture, BaseUnit * 15, y_coor, unit);
	}
	if (level > 60) {
		addLight(window, listLightTexture, BaseUnit * 25, y_coor, unit);
	}
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
		Vehicle* Tem = v;
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
		Vehicle* Tem = v;
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
		else car->draw(listLight[0].getState(), listLight[0].getPos(dir));
	}
	for (auto& light : listLight) light.draw();
	for (auto& obs : listObstacle) obs.draw();
}

void Road::handleEvent() {
	//return;
	for (int i = 0; i < listVehicle.size(); ++i) {
		/*if (listLight.size() == 0) car->move(0, 0);
		else {
			car->move(listLight[0].getState(), listLight[0].getPos());
		}*/
		Vehicle* car = listVehicle[i];
		float preCarPos = -1;
		for (int j = 0; j < listVehicle.size(); ++j) {
			if (j == i) continue;
			Vehicle* preCar = listVehicle[j];
			if (((preCar->getPosHigh() > car->getPosHigh()) == (dir == 1))) {
				if (preCarPos == -1 || ((preCarPos > preCar->getPosLow()) == (dir == 1))) {
					preCarPos = preCar->getPosLow();
				}
			}
		}
		if (preCarPos != -1 && ((preCarPos < car->getPosHigh()) == (dir == 1))) {
			preCarPos = car->getPosHigh();
		}
		int low = 0, high = (int)listLight.size() - 1, pos = -1;
		while (low <= high) {
			int mid = (low + high) / 2;
			if (car->isPass(listLight[mid].getState(), listLight[mid].getPos(dir))) {
				if (car->getDir() == 1) low = mid + 1;
				else high = mid - 1;
			}
			else {
				pos = mid;
				if (car->getDir() == 1) high = mid - 1;
				else low = mid + 1;
			}
		}
		if (pos == -1) {
			if (preCarPos == -1) car->move(0, 0);
			else car->move(2, preCarPos);
		}
		else {
			if(preCarPos == -1 || ((listLight[pos].getPos(dir) < preCarPos) == (dir == 1)) || abs(listLight[pos].getPos(dir) - preCarPos) <= 0.001 ) car->move(listLight[pos].getState(), listLight[pos].getPos(dir));
			else {
				car->move(2, preCarPos);
			}
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

RailWay::RailWay(RenderWindow& window, int dir, Texture& texture, int x_coor, int y_coor, int unit, vector<Texture>& mTexture, int level) :
	window(&window)
{
	this->dir = dir;
	this->y_coor = y_coor;
	this->unit = unit;
	this->mTexture = mTexture;
	for (int i = 0; i < 1; ++i) {
		Vehicle* Tem = new Train(0.2, 0.3, window, texture, x_coor, y_coor, dir, unit);
		listVehicle.push_back(Tem);
	}
	generate(window, listTexture, mTexture, unit, y_coor);
}

RailWay::RailWay(RenderWindow& window, int dir, int numLight, vector<Texture>& listLightTexture, Texture& texture, int x_coor, int y_coor, int unit, vector<Texture>& mTexture, int level) :
	window(&window)
{
	this->dir = dir;
	this->y_coor = y_coor;
	this->unit = unit;
	this->mTexture = mTexture;
	for (int i = 0; i < 1; ++i) {
		Vehicle* Tem = new Train(0.2, 0.3, window, texture, x_coor, y_coor, dir, unit);
		listVehicle.push_back(Tem);
	}
	generate(window, listTexture, mTexture, unit, y_coor);
	addLight(window, listLightTexture, BaseUnit * 5, y_coor, unit);
	addLight(window, listLightTexture, BaseUnit * 15, y_coor, unit);
	addLight(window, listLightTexture, BaseUnit * 25, y_coor, unit);
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
		Vehicle* Tem = v;
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
	for (auto& train : listVehicle) {
		train->draw();
	}
	for (auto& light : listLight) light.draw();
}

void RailWay::handleEvent() {
	//return;
	for (auto& train : listVehicle) {
		bool isMove = train->move(0, 0);
		for (auto& light : listLight) {
			if (isMove) light.setState(2);
			else light.setState(0);
		}
	}
}

bool RailWay::isCollided(Player& mPlayer)
{
	for (auto& train : listVehicle) if (mPlayer.isCollided(*train)) return true;
	return false;
}

int RailWay::getPosition() {
	return y_coor;
}