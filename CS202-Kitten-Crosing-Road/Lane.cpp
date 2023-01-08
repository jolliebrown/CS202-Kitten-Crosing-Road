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
	this->dir = 1;
	this->y_coor = y_coor;
	this->unit = unit;
	this->mTexture = mTexture;
	generate(window, listTexture, mTexture, unit, y_coor);
	addObstacle(window, listTextureObstacle, BaseUnit * (5 + Rand(1, 3)) , y_coor, unit);
	addObstacle(window, listTextureObstacle, BaseUnit * (10 + Rand(1, 3)), y_coor, unit);
	addObstacle(window, listTextureObstacle, BaseUnit * (15 + Rand(1, 3)), y_coor, unit);
}

Road::Road(RenderWindow& window, int x_coor, int y_coor, int unit, vector<Texture>& listTextureObstacle, vector<Texture>& mTexture, ifstream& is) :
	window(&window)
{
	this->dir = dir;
	this->y_coor = y_coor;
	this->unit = unit;
	this->mTexture = mTexture;
	generate(window, listTexture, mTexture, unit, y_coor);
	int numObs;
	is >> numObs;
	for (int i = 0; i < numObs; ++i) {
		float vx_coor, vy_coor;
		is >> vx_coor >> vy_coor;
		addObstacle(window, listTextureObstacle, vx_coor, vy_coor, unit);
	}
}

Road::Road(RenderWindow& window, int dir, int numLight, vector<Texture>& listLightTexture, vector<Texture>& listAnimalTexture, vector<Texture>& listCarTexture, int x_coor, int y_coor, int unit, vector<Texture>& mTexture, int level) :
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
	float velo = 0.03 + float(level / 5) * 0.01;
	int random_num = Rand(0, 1500);
	int distance_car = max(int(100 / velo), 2000);
	for (int i = 0; i <= numCars; ++i) {
		//Vehicle* Tem = new Car(velo, velo, window, texture, x_coor, y_coor, dir, unit);
		Vehicle* Tem;
		if (i > 0) Tem = new Car(milliseconds(random_num + distance_car * i), velo, velo, window, listCarTexture[Rand(1, 100) % 3], x_coor, y_coor, dir, unit);
		else Tem = new Animal(milliseconds(random_num + distance_car * i), velo, velo, window, listAnimalTexture, x_coor, y_coor, dir, unit);
		listVehicle.push_back(Tem);
		for (int j = 0; j < i; j++)
		{
			listVehicle[i]->restartClock();
		}
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

Road::Road(RenderWindow& window, int dir, int numLight, vector<Texture>& listLightTexture, vector<Texture>& listAnimalTexture, vector<Texture>& listCarTexture, int x_coor, int y_coor, int unit, vector<Texture>& mTexture, int level, ifstream &is) :
	window(&window)
{
	this->dir = dir;
	this->y_coor = y_coor;
	this->unit = unit;
	this->mTexture = mTexture;
	int numCars;

	int vtype;
	float vx_coor, vy_coor, vvelo, vlimvelo, vinitvelo, vacce, vtime;
	int vdir, vstate;

	is >> numCars;
	for (int i = 0; i < numCars; ++i) {
		//Vehicle* Tem = new Car(velo, velo, window, texture, x_coor, y_coor, dir, unit);
		Vehicle* Tem;
		is >> vtype;

		is >> vx_coor >> vy_coor >> vdir >> vlimvelo >> vinitvelo >> vvelo >> vacce >> vtime;
		if (vtype == 1) Tem = new Car(milliseconds(vtime), vvelo, vinitvelo, vlimvelo, window, listCarTexture[Rand(1, 100) % 3], vx_coor, vy_coor, vdir, unit);
		else Tem = new Animal(milliseconds(vtime), vvelo, vinitvelo, vlimvelo, window, listAnimalTexture, vx_coor, vy_coor, vdir, unit);
		listVehicle.push_back(Tem);
		for (int j = 0; j < i; j++)
		{
			listVehicle[i]->restartClock();
		}
	}
	generate(window, listTexture, mTexture, unit, y_coor);
	is >> numLight;
	for (int i = 0; i < numLight; ++i) {
		is >> vx_coor >> vy_coor >> vstate;
		addLight(window, listLightTexture, vx_coor, vy_coor, unit);
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

void Road::addLight(RenderWindow& window, vector<Texture>& texture, int state, int x_coor, int y_coor, int unit)
{
	listLight.push_back(Light(state, window, texture, x_coor, y_coor - 5, unit));
}



void Road::draw(bool onlyLane)
{
	if (onlyLane) {
		for (unsigned int i = 0; i < listTexture.size(); i++)
		{
			listTexture[i].draw();
		}
	}
	else {
		for (auto& car : listVehicle) {
			if (listLight.size() == 0) car->draw();
			else car->draw(listLight[0].getState(), listLight[0].getPos(dir));
		}
		for (auto& light : listLight) light.draw();
		for (auto& obs : listObstacle) obs.draw();
	}
}

void Road::resetVehicle() {
	for (auto& car : listVehicle) {
		car->reset();
	}
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
	for (auto& car : listVehicle) {
		if (mPlayer.isCollided(*car))
		{
			car->playSound();
			return true;
		}
	}
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

RailWay::RailWay(RenderWindow& window, int dir, int numLight, vector<Texture>& listLightTexture, Texture& texture, int x_coor, int y_coor, int unit, vector<Texture>& mTexture, int level) :
	window(&window)
{
	this->dir = dir;
	this->y_coor = y_coor;
	this->unit = unit;
	this->mTexture = mTexture;
	for (int i = 0; i < 1; ++i) {
		Vehicle* Tem = new Train(0.3, 0.4, window, texture, x_coor, y_coor, dir, unit);
		listVehicle.push_back(Tem);
	}
	generate(window, listTexture, mTexture, unit, y_coor);
	addLight(window, listLightTexture, BaseUnit * 5, y_coor, unit);
	addLight(window, listLightTexture, BaseUnit * 15, y_coor, unit);
	addLight(window, listLightTexture, BaseUnit * 25, y_coor, unit);
}

RailWay::RailWay(RenderWindow& window, int dir, int numLight, vector<Texture>& listLightTexture, Texture& texture, int x_coor, int y_coor, int unit, vector<Texture>& mTexture, int level, ifstream &is) :
	window(&window)
{
	this->dir = dir;
	this->y_coor = y_coor;
	this->unit = unit;
	this->mTexture = mTexture;

	int numTrain;
	is >> numTrain;

	int vtype, vdir, vstate;
	float vx_coor, vy_coor, vlimvelo, vinitvelo, vvelo, vacce, vtime;
	for (int i = 0; i < numTrain; ++i) {
		is >> vtype >> vx_coor >> vy_coor >> vdir >> vlimvelo >> vinitvelo >> vvelo >> vacce >> vtime;
		Vehicle* Tem = new Train(milliseconds(vtime), vvelo, vinitvelo, vlimvelo, window, texture, vx_coor, vy_coor, vdir, unit);
		listVehicle.push_back(Tem);
	}
	generate(window, listTexture, mTexture, unit, y_coor);
	is >> numLight;
	for (int i = 0; i < numLight; ++i) {
		is >> vx_coor >> vy_coor >> vstate;
		addLight(window, listLightTexture, vx_coor, vy_coor, unit);
	}
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

void RailWay::draw(bool onlyLane)
{
	if (onlyLane) {
		for (unsigned int i = 0; i < listTexture.size(); i++)
		{
			listTexture[i].draw();
		}
	}
	else {
		for (auto& train : listVehicle) {
			train->draw();
		}
		for (auto& light : listLight) light.draw();
	}
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

/// *********************** Water ******************** ///
Water::Water()
{
	dir = 0;
	y_coor = 0;
	unit = 0;
}

void Water::addObstacle(RenderWindow& window, vector<Texture>& texture, int x_coor, int y_coor, int unit)
{
	int k = Rand(1, 100) % 2;
	listObstacle.push_back(Obstacle(window, texture[k], x_coor, y_coor - 5, unit));
}

//Water::Water(RenderWindow& window, int x_coor, int y_coor, int unit, vector<Texture>& listTextureObstacle, vector<Texture>& mTexture) :
//	window(&window)
//{
//	this->dir = dir;
//	this->y_coor = y_coor;
//	this->unit = unit;
//	this->mTexture = mTexture;
//	generate(window, listTexture, mTexture, unit, y_coor);
//	addObstacle(window, listTextureObstacle, BaseUnit * (5 + Rand(1, 3)), y_coor, unit);
//	addObstacle(window, listTextureObstacle, BaseUnit * (10 + Rand(1, 3)), y_coor, unit);
//	addObstacle(window, listTextureObstacle, BaseUnit * (15 + Rand(1, 3)), y_coor, unit);
//}

Water::Water(RenderWindow& window, int dir, Texture& texture, int x_coor, int y_coor, int unit, vector<Texture>& mTexture, int level) :
	window(&window)
{
	this->dir = dir;
	this->y_coor = y_coor;
	this->unit = unit;
	this->mTexture = mTexture;
	int numWoods = 6;
	if (level > 20) {
		numWoods++;
	}
	if (level > 40) {
		numWoods++;
	}
	if (level > 60) {
		numWoods++;
	}
	float velo = 0.03 + (level / 20) * 0.005;
	int random_num = Rand(0, 500);
	int distance_car = max(int(100 / velo), 500);
	for (int i = 0; i <= numWoods; ++i) {
		//Vehicle* Tem = new Car(velo, velo, window, texture, x_coor, y_coor, dir, unit);
		Vehicle* Tem;
		Tem = new Wood(milliseconds(random_num + distance_car * i), velo, velo, window, texture, x_coor, y_coor, dir, unit);
		listVehicle.push_back(Tem);
		for (int j = 0; j < i; j++)
		{
			listVehicle[i]->restartClock();
		}
	}
	generate(window, listTexture, mTexture, unit, y_coor);
}

Water::Water(RenderWindow& window, int dir, Texture& texture, int x_coor, int y_coor, int unit, vector<Texture>& mTexture, int level, ifstream& is) :
	window(&window)
{
	this->dir = dir;
	this->y_coor = y_coor;
	this->unit = unit;
	this->mTexture = mTexture;
	int numWoods;
	is >> numWoods;
	
	int vtype, vdir;
	float vx_coor, vy_coor, vvelo, vinitvelo, vlimvelo, vtime, vacce;
	for (int i = 0; i <= numWoods; ++i) {
		is >> vtype >> vx_coor >> vy_coor >> vdir >> vlimvelo >> vinitvelo >> vvelo >> vacce >> vtime;
		Vehicle* Tem;
		Tem = new Wood(milliseconds(vtime), vvelo, vinitvelo, vlimvelo, window, texture, vx_coor, vy_coor, vdir, unit);
		listVehicle.push_back(Tem);
		for (int j = 0; j < i; j++)
		{
			listVehicle[i]->restartClock();
		}
	}
	generate(window, listTexture, mTexture, unit, y_coor);
}

Water::Water(const Water& road) :
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
}

Water& Water::operator = (const Water& road)
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
	return *this;
}

vector<Object>& Water::generate(RenderWindow& window, vector<Object>& res, vector<Texture>& texture, int unit, int pos)
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

void Water::addLight(RenderWindow& window, vector<Texture>& texture, int x_coor, int y_coor, int unit)
{
	
}

void Water::draw(bool onlyLane)
{
	if (onlyLane) {
		for (unsigned int i = 0; i < listTexture.size(); i++)
		{
			listTexture[i].draw();
		}
	}
	else {
		for (auto& wood : listVehicle) {
			wood->draw();
		}
		for (auto& obs : listObstacle) obs.draw();
	}
}

void Water::handleEvent() {
	//return;
	for (auto wood: listVehicle) {
		wood->move(0, 0);
	}
}

bool Water::isCollided(Player& mPlayer)
{
	for (auto& wood : listVehicle) {
		if (mPlayer.isCollided(*wood)) {
			mPlayer.movePosition(wood->getVelo(), 0);
			return false;
		}
	}
	FloatRect water(0, y_coor + 2, BaseUnit * 30, BaseUnit - 4);
	if (mPlayer.isCollidedWater(water)) return true;
	return false;
}

int Water::getPosition() {
	return y_coor;
}

void Water::resetVehicle() {

}

void RailWay::resetVehicle() {
	for (auto& train : listVehicle) {
		train->reset();
	}
}

int Road::getDir()
{
	return dir;
}

int RailWay::getDir()
{
	return dir;
}

int Water::getDir()
{
	return dir;
}

// Save map
void Road::saveMap(ofstream& os)
{
	if (listVehicle.size() == 0) {
		// grass
		os << 0 << '\n';
		// postion y
		os << y_coor << '\n';
		os << dir << '\n';
		os << listObstacle.size() << '\n';
		for (auto& obs : listObstacle) obs.saveMap(os);
	}
	else {
		os << 1 << '\n';
		os << y_coor << '\n';
		os << dir << '\n';
		os << listVehicle.size() << '\n';
		for (auto& vehicle : listVehicle) vehicle->saveMap(os);
		os << listLight.size() << '\n';
		for (auto& light : listLight) light.saveMap(os);
	}
}

void RailWay::saveMap(ofstream& os)
{
	os << 2 << '\n';
	os << y_coor << '\n';
	os << dir << '\n';
	os << listVehicle.size() << '\n';
	for (auto& vehicle : listVehicle) vehicle->saveMap(os);
	os << listLight.size() << '\n';
	for (auto& light : listLight) light.saveMap(os);
}

void Water::saveMap(ofstream& os)
{
	os << 3 << '\n';
	os << y_coor << '\n';
	os << dir << '\n';
	os << listVehicle.size() << '\n';
	for (auto& vehicle : listVehicle) vehicle->saveMap(os);
}
