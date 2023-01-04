#include "Vehicle.h"

int Rand(int l, int r)
{
	int t = RAND_MAX;
	return l + (rand() * t + rand() * t + rand()) % (r - l + 1);
}

Vehicle::Vehicle(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit) :
	Object(window, texture, x_coor, y_coor, unit)
{
	buffer.loadFromFile("Media/SFX/Car.wav");
	sound.setBuffer(buffer);
}

// Constructor
Car::Car(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit) :
	Vehicle(window, texture, x_coor, y_coor, unit)
{
	dir = _dir; limVelo = dir * 0.2; initVelo = dir * 0.1; velo = dir * initVelo; acce = dir * 0.01;

	startPoint = (dir == 1) ? -Object::asset.getGlobalBounds().width : BaseUnit * 29 + Object::asset.getGlobalBounds().width;
	endPoint = (dir == 1) ? BaseUnit * 29 + Object::asset.getGlobalBounds().width : -Object::asset.getGlobalBounds().width;


	if (dir == -1) Object::asset.setTextureRect(IntRect(Object::asset.getGlobalBounds().width, 0, -Object::asset.getGlobalBounds().width, Object::asset.getGlobalBounds().height));
	Object::asset.setOrigin(Object::asset.getGlobalBounds().width / 2, Object::asset.getGlobalBounds().height / 2);

	clock.restart();
	startMoveTime = milliseconds(Rand(1000, 8000));
	coord = Vector2f(x_coor, (float)(y_coor + 16 / 2));
	Object::asset.setPosition(startPoint, coord.y);
}

Car::Car(float initVelo, float limVelo, RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit) :
	Vehicle(window, texture, x_coor, y_coor, unit)
{
	dir = _dir; this->limVelo = dir * limVelo; this->initVelo = dir * initVelo; velo = dir * initVelo; acce = dir * 0.01;

	startPoint = (dir == 1) ? -Object::asset.getGlobalBounds().width : BaseUnit * 29 + Object::asset.getGlobalBounds().width;
	endPoint = (dir == 1) ? BaseUnit * 29 + Object::asset.getGlobalBounds().width : -Object::asset.getGlobalBounds().width;

	if (dir == -1) Object::asset.setTextureRect(IntRect(Object::asset.getGlobalBounds().width, 0, -Object::asset.getGlobalBounds().width, Object::asset.getGlobalBounds().height));
	Object::asset.setOrigin(Object::asset.getGlobalBounds().width / 2, Object::asset.getGlobalBounds().height / 2);

	clock.restart();
	startMoveTime = milliseconds(Rand(1000, 8000));
	coord = Vector2f(x_coor, (float)(y_coor + 16 / 2));
	Object::asset.setPosition(startPoint, coord.y);
}

Car::Car(Time moveTime, float initVelo, float limVelo, RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit) :
	Vehicle(window, texture, x_coor, y_coor, unit)
{
	dir = _dir; this->limVelo = dir * limVelo; this->initVelo = dir * initVelo; velo = dir * initVelo; acce = dir * 0.01;

	startPoint = (dir == 1) ? -Object::asset.getGlobalBounds().width : BaseUnit * 29 + Object::asset.getGlobalBounds().width;
	endPoint = (dir == 1) ? BaseUnit * 29 + Object::asset.getGlobalBounds().width : -Object::asset.getGlobalBounds().width;

	if (dir == -1) Object::asset.setTextureRect(IntRect(Object::asset.getGlobalBounds().width, 0, -Object::asset.getGlobalBounds().width, Object::asset.getGlobalBounds().height));
	Object::asset.setOrigin(Object::asset.getGlobalBounds().width / 2, Object::asset.getGlobalBounds().height / 2);

	clock.restart();
	startMoveTime = moveTime;
	coord = Vector2f(x_coor, (float)(y_coor + 16 / 2));
	Object::asset.setPosition(startPoint, coord.y);
}

Car::Car(const Car& vehicle):
	Vehicle(vehicle), coord(vehicle.coord), startPoint(vehicle.startPoint), endPoint(vehicle.endPoint),
	velo(vehicle.velo), limVelo(vehicle.limVelo), initVelo(vehicle.initVelo), acce(vehicle.acce),
	startMoveTime(vehicle.startMoveTime), clock(vehicle.clock), dir(vehicle.dir)
{
	if (dir == -1) Object::asset.setTextureRect(IntRect(Object::asset.getGlobalBounds().width, 0, -Object::asset.getGlobalBounds().width, Object::asset.getGlobalBounds().height));
	Object::asset.setOrigin(Object::asset.getGlobalBounds().width / 2, Object::asset.getGlobalBounds().height / 2);
	Object::asset.setPosition(startPoint, coord.y);
}

void Car::draw(int state, float x_coord)
{
	Object::draw();
	/*move(state, x_coord);*/
}

void Car::accelerate()
{
	velo += acce;
	if ((velo > limVelo) == (dir == 1)) velo = limVelo;
}

bool Car::move(int state, float x_coord)
{
	if (clock.getElapsedTime().asMilliseconds() < startMoveTime.asMilliseconds()) return false;
	Object::asset.move(Vector2f(velo, 0));
	checkLight(state, x_coord);
	if ((Object::asset.getPosition().x > endPoint) == (dir == 1)) {
		Object::asset.setPosition(startPoint, coord.y);
		clock.restart();
		startMoveTime = seconds(0);
		velo = initVelo;
	}
	return true;
}

void Car::checkLight(int state, float x_coord)
{
	float x_car = getPosHigh();
	if (state == 0 || (((x_car > x_coord) == (dir == 1)) && x_car != x_coord)) {
		accelerate();
		//if (insideView()) sound.play();
		return;
	} 
	velo = min(abs(velo), abs(x_coord - x_car)) * dir;
}

bool Car::isPass(int state, float x_coord)
{
	float x_car = dir * Object::asset.getGlobalBounds().width / 2 + Object::asset.getPosition().x;
	return (((x_car > x_coord) == (dir == 1)) && x_car != x_coord);
}

int Car::getDir()
{
	return dir;
}

float Car::getPosLow()
{
	return Object::asset.getPosition().x + (-dir) * Object::asset.getGlobalBounds().width / 2.0;
}

float Car::getPosHigh()
{
	return Object::asset.getPosition().x + dir * Object::asset.getGlobalBounds().width / 2.0;
}

void Car::restartClock()
{
	clock.restart();
}

// Constructor
Animal::Animal(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit) :
	Vehicle(window, texture, x_coor, y_coor, unit)
{
	dir = _dir; limVelo = dir * 0.2; initVelo = dir * 0.1; velo = dir * initVelo; acce = dir * 0.01;

	startPoint = (dir == 1) ? -Object::asset.getGlobalBounds().width : BaseUnit * 29 + Object::asset.getGlobalBounds().width;
	endPoint = (dir == 1) ? BaseUnit * 29 + Object::asset.getGlobalBounds().width : -Object::asset.getGlobalBounds().width;

	Object::asset.setOrigin(Object::asset.getGlobalBounds().width / 2, Object::asset.getGlobalBounds().height / 2);
	if (dir == -1) Object::asset.rotate(180);

	clock.restart();
	startMoveTime = milliseconds(Rand(1000, 8000));
	coord = Vector2f(x_coor, (float)(y_coor + 16 / 2));
	Object::asset.setPosition(startPoint, coord.y);
}

Animal::Animal(float initVelo, float limVelo, RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit) :
	Vehicle(window, texture, x_coor, y_coor, unit)
{
	dir = _dir; this->limVelo = dir * limVelo; this->initVelo = dir * initVelo; velo = dir * initVelo; acce = dir * 0.01;

	startPoint = (dir == 1) ? -Object::asset.getGlobalBounds().width : BaseUnit * 29 + Object::asset.getGlobalBounds().width;
	endPoint = (dir == 1) ? BaseUnit * 29 + Object::asset.getGlobalBounds().width : -Object::asset.getGlobalBounds().width;

	Object::asset.setOrigin(Object::asset.getGlobalBounds().width / 2, Object::asset.getGlobalBounds().height / 2);
	if (dir == -1) Object::asset.rotate(180);

	clock.restart();
	startMoveTime = milliseconds(Rand(1000, 8000));
	coord = Vector2f(x_coor, (float)(y_coor + 16 / 2));
	Object::asset.setPosition(startPoint, coord.y);
}

Animal::Animal(Time moveTime, float initVelo, float limVelo, RenderWindow& window, vector<Texture>& texture, int x_coor, int y_coor, int _dir, int unit) :
	Vehicle(window, texture[0], x_coor, y_coor, unit)
{
	dir = _dir; this->limVelo = dir * limVelo; this->initVelo = dir * initVelo; velo = dir * initVelo; acce = dir * 0.01;

	startPoint = (dir == 1) ? -Object::asset.getGlobalBounds().width : BaseUnit * 29 + Object::asset.getGlobalBounds().width;
	endPoint = (dir == 1) ? BaseUnit * 29 + Object::asset.getGlobalBounds().width : -Object::asset.getGlobalBounds().width;

	if(dir == -1) Object::asset.setTextureRect(IntRect(Object::asset.getGlobalBounds().width, 0, -Object::asset.getGlobalBounds().width, Object::asset.getGlobalBounds().height));
	Object::asset.setOrigin(Object::asset.getGlobalBounds().width / 2, Object::asset.getGlobalBounds().height / 2);
	//if (dir == -1) Object::asset.rotate(180);

	curView = 0;
	listTexture = texture;
	clock.restart();
	startMoveTime = moveTime;
	coord = Vector2f(x_coor, (float)(y_coor + 16 / 2));
	Object::asset.setPosition(startPoint, coord.y);
}

Animal::Animal(const Animal& vehicle) :
	Vehicle(vehicle), coord(vehicle.coord), startPoint(vehicle.startPoint), endPoint(vehicle.endPoint),
	velo(vehicle.velo), limVelo(vehicle.limVelo), initVelo(vehicle.initVelo), acce(vehicle.acce),
	startMoveTime(vehicle.startMoveTime), clock(vehicle.clock), dir(vehicle.dir)
{
	Object::asset.setOrigin(Object::asset.getGlobalBounds().width / 2, Object::asset.getGlobalBounds().height / 2);
	if (dir == -1) Object::asset.rotate(180);
	Object::asset.setPosition(startPoint, coord.y);
}

void Animal::draw(int state, float x_coord)
{
	Object::draw();
	/*move(state, x_coord);*/
}

void Animal::accelerate()
{
	velo += acce;
	if ((velo > limVelo) == (dir == 1)) velo = limVelo;
}

bool Animal::move(int state, float x_coord)
{
	if (clock.getElapsedTime().asMilliseconds() < startMoveTime.asMilliseconds()) return false;
	Object::asset.move(Vector2f(velo, 0));
	if (clock.getElapsedTime().asMilliseconds() % 100 == 0) {
		curView = (curView + 1) % listTexture.size();
		if(curView % 2 == 1) curView = (curView + 1) % listTexture.size();
		Object::asset.setTexture(listTexture[curView]);
		if (dir == -1) Object::asset.setTextureRect(IntRect(Object::asset.getGlobalBounds().width, 0, -Object::asset.getGlobalBounds().width, Object::asset.getGlobalBounds().height));
	}

	checkLight(state, x_coord);
	if ((Object::asset.getPosition().x > endPoint) == (dir == 1)) {
		Object::asset.setPosition(startPoint, coord.y);
		clock.restart();
		startMoveTime = seconds(0);
		velo = initVelo;
	}
	return true;
}

void Animal::checkLight(int state, float x_coord)
{
	return;
	float x_car = getPosHigh();
	if (state == 0 || (((x_car > x_coord) == (dir == 1)) && x_car != x_coord)) {
		accelerate();
		//if (insideView()) sound.play();
		return;
	}
	velo = min(abs(velo), abs(x_coord - x_car)) * dir;
}

bool Animal::isPass(int state, float x_coord)
{
	float x_car = dir * Object::asset.getGlobalBounds().width / 2 + Object::asset.getPosition().x;
	return (((x_car > x_coord) == (dir == 1)) && x_car != x_coord);
}

int Animal::getDir()
{
	return dir;
}

float Animal::getPosLow()
{
	return Object::asset.getPosition().x + (-dir) * Object::asset.getGlobalBounds().width / 2.0;
}

float Animal::getPosHigh()
{
	return Object::asset.getPosition().x + dir * Object::asset.getGlobalBounds().width / 2.0;
}

void Animal::restartClock()
{
	clock.restart();
}

/// Train ///
Train::Train(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit) :
	Vehicle(window, texture, x_coor, y_coor, unit)
{
	dir = _dir; limVelo = dir * 0.2; initVelo = dir * 0.1; velo = dir * initVelo; acce = dir * 0.01;

	startPoint = (dir == 1) ? -Object::asset.getGlobalBounds().width : BaseUnit * 29 + Object::asset.getGlobalBounds().width;
	endPoint = (dir == 1) ? BaseUnit * 29 + Object::asset.getGlobalBounds().width : -Object::asset.getGlobalBounds().width;

	Object::asset.setOrigin(Object::asset.getGlobalBounds().width / 2, Object::asset.getGlobalBounds().height / 2);
	if (dir == -1) Object::asset.rotate(180);

	clock.restart();
	startMoveTime = milliseconds(Rand(1000, 8000));
	coord = Vector2f(x_coor, (float)(y_coor + 16 / 2));
	Object::asset.setPosition(startPoint, coord.y);
}

Train::Train(float initVelo, float limVelo, RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit) :
	Vehicle(window, texture, x_coor, y_coor, unit)
{
	dir = _dir; this->limVelo = dir * limVelo; this->initVelo = dir * initVelo; velo = dir * initVelo; acce = dir * 0.01;

	startPoint = (dir == 1) ? -Object::asset.getGlobalBounds().width : BaseUnit * 29 + Object::asset.getGlobalBounds().width;
	endPoint = (dir == 1) ? BaseUnit * 29 + Object::asset.getGlobalBounds().width : -Object::asset.getGlobalBounds().width;

	Object::asset.setOrigin(Object::asset.getGlobalBounds().width / 2, Object::asset.getGlobalBounds().height / 2);
	if (dir == -1) Object::asset.rotate(180);

	clock.restart();
	startMoveTime = milliseconds(Rand(1000, 8000));
	coord = Vector2f(x_coor, (float)(y_coor + 16 / 2));
	Object::asset.setPosition(startPoint, coord.y);
}

Train::Train(const Train& vehicle) :
	Vehicle(vehicle), coord(vehicle.coord), startPoint(vehicle.startPoint), endPoint(vehicle.endPoint),
	velo(vehicle.velo), limVelo(vehicle.limVelo), initVelo(vehicle.initVelo), acce(vehicle.acce),
	startMoveTime(vehicle.startMoveTime), clock(vehicle.clock), dir(vehicle.dir)
{
	Object::asset.setOrigin(Object::asset.getGlobalBounds().width / 2, Object::asset.getGlobalBounds().height / 2);
	if (dir == -1) Object::asset.rotate(180);
	Object::asset.setPosition(startPoint, coord.y);
}

void Train::draw(int state, float x_coord)
{
	Object::draw();
	/*move(state, x_coord);*/
}

void Train::accelerate()
{
	velo += acce;
	if ((velo > limVelo) == (dir == 1)) velo = limVelo;
}

bool Train::move(int state, float x_coord)
{
	if (clock.getElapsedTime().asMilliseconds() < startMoveTime.asMilliseconds()) return false;
	Object::asset.move(Vector2f(velo, 0));
	checkLight(state, x_coord);
	if ((Object::asset.getPosition().x > endPoint) == (dir == 1)) {
		Object::asset.setPosition(startPoint, coord.y);
		clock.restart();
		startMoveTime = milliseconds(Rand(1000, 8000));
		velo = initVelo;
	}
	return true;
}

void Train::checkLight(int state, float x_coord)
{
	
}

bool Train::isPass(int state, float x_coord)
{
	float x_car = dir * Object::asset.getGlobalBounds().width / 2 + Object::asset.getPosition().x;
	return (((x_car > x_coord) == (dir == 1)) && x_car != x_coord);
}

int Train::getDir()
{
	return dir;
}

float Train::getPosLow()
{
	return Object::asset.getPosition().x + (-dir) * Object::asset.getGlobalBounds().width / 2.0;
}

float Train::getPosHigh()
{
	return Object::asset.getPosition().x + dir * Object::asset.getGlobalBounds().width / 2.0;
}

void Train::restartClock()
{
	clock.restart();
}

// Constructor
Wood::Wood(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit) :
	Vehicle(window, texture, x_coor, y_coor, unit)
{
	dir = _dir; limVelo = dir * 0.2; initVelo = dir * 0.1; velo = dir * initVelo; acce = dir * 0.01;

	startPoint = (dir == 1) ? -Object::asset.getGlobalBounds().width : BaseUnit * 29 + Object::asset.getGlobalBounds().width;
	endPoint = (dir == 1) ? BaseUnit * 29 + Object::asset.getGlobalBounds().width : -Object::asset.getGlobalBounds().width;


	if (dir == -1) Object::asset.setTextureRect(IntRect(Object::asset.getGlobalBounds().width, 0, -Object::asset.getGlobalBounds().width, Object::asset.getGlobalBounds().height));
	Object::asset.setOrigin(Object::asset.getGlobalBounds().width / 2, Object::asset.getGlobalBounds().height / 2);

	clock.restart();
	startMoveTime = milliseconds(Rand(1000, 8000));
	coord = Vector2f(x_coor, (float)(y_coor + 16 / 2));
	Object::asset.setPosition(startPoint, coord.y);
}

Wood::Wood(float initVelo, float limVelo, RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit) :
	Vehicle(window, texture, x_coor, y_coor, unit)
{
	dir = _dir; this->limVelo = dir * limVelo; this->initVelo = dir * initVelo; velo = dir * initVelo; acce = dir * 0.01;

	startPoint = (dir == 1) ? -Object::asset.getGlobalBounds().width : BaseUnit * 29 + Object::asset.getGlobalBounds().width;
	endPoint = (dir == 1) ? BaseUnit * 29 + Object::asset.getGlobalBounds().width : -Object::asset.getGlobalBounds().width;

	if (dir == -1) Object::asset.setTextureRect(IntRect(Object::asset.getGlobalBounds().width, 0, -Object::asset.getGlobalBounds().width, Object::asset.getGlobalBounds().height));
	Object::asset.setOrigin(Object::asset.getGlobalBounds().width / 2, Object::asset.getGlobalBounds().height / 2);

	clock.restart();
	startMoveTime = milliseconds(Rand(1000, 8000));
	coord = Vector2f(x_coor, (float)(y_coor + 16 / 2));
	Object::asset.setPosition(startPoint, coord.y);
}

Wood::Wood(Time moveTime, float initVelo, float limVelo, RenderWindow& window, Texture& texture, int x_coor, int y_coor, int _dir, int unit) :
	Vehicle(window, texture, x_coor, y_coor, unit)
{
	dir = _dir; this->limVelo = dir * limVelo; this->initVelo = dir * initVelo; velo = dir * initVelo; acce = dir * 0.01;

	startPoint = (dir == 1) ? -Object::asset.getGlobalBounds().width : BaseUnit * 29 + Object::asset.getGlobalBounds().width;
	endPoint = (dir == 1) ? BaseUnit * 29 + Object::asset.getGlobalBounds().width : -Object::asset.getGlobalBounds().width;

	if (dir == -1) Object::asset.setTextureRect(IntRect(Object::asset.getGlobalBounds().width, 0, -Object::asset.getGlobalBounds().width, Object::asset.getGlobalBounds().height));
	Object::asset.setOrigin(Object::asset.getGlobalBounds().width / 2, Object::asset.getGlobalBounds().height / 2);

	clock.restart();
	startMoveTime = moveTime;
	coord = Vector2f(x_coor, (float)(y_coor + 16 / 2));
	Object::asset.setPosition(startPoint, coord.y);
}

Wood::Wood(const Wood& vehicle) :
	Vehicle(vehicle), coord(vehicle.coord), startPoint(vehicle.startPoint), endPoint(vehicle.endPoint),
	velo(vehicle.velo), limVelo(vehicle.limVelo), initVelo(vehicle.initVelo), acce(vehicle.acce),
	startMoveTime(vehicle.startMoveTime), clock(vehicle.clock), dir(vehicle.dir)
{
	if (dir == -1) Object::asset.setTextureRect(IntRect(Object::asset.getGlobalBounds().width, 0, -Object::asset.getGlobalBounds().width, Object::asset.getGlobalBounds().height));
	Object::asset.setOrigin(Object::asset.getGlobalBounds().width / 2, Object::asset.getGlobalBounds().height / 2);
	Object::asset.setPosition(startPoint, coord.y);
}

void Wood::draw(int state, float x_coord)
{
	Object::draw();
	/*move(state, x_coord);*/
}

void Wood::accelerate()
{
	velo += acce;
	if ((velo > limVelo) == (dir == 1)) velo = limVelo;
}

bool Wood::move(int state, float x_coord)
{
	if (clock.getElapsedTime().asMilliseconds() < startMoveTime.asMilliseconds()) return false;
	Object::asset.move(Vector2f(velo, 0));
	checkLight(state, x_coord);
	if ((Object::asset.getPosition().x > endPoint) == (dir == 1)) {
		Object::asset.setPosition(startPoint, coord.y);
		clock.restart();
		startMoveTime = seconds(0);
		velo = initVelo;
	}
	return true;
}

void Wood::checkLight(int state, float x_coord)
{
	float x_car = getPosHigh();
	if (state == 0 || (((x_car > x_coord) == (dir == 1)) && x_car != x_coord)) {
		accelerate();
		//if (insideView()) sound.play();
		return;
	}
	velo = min(abs(velo), abs(x_coord - x_car)) * dir;
}

bool Wood::isPass(int state, float x_coord)
{
	float x_car = dir * Object::asset.getGlobalBounds().width / 2 + Object::asset.getPosition().x;
	return (((x_car > x_coord) == (dir == 1)) && x_car != x_coord);
}

int Wood::getDir()
{
	return dir;
}

float Wood::getPosLow()
{
	return Object::asset.getPosition().x + (-dir) * Object::asset.getGlobalBounds().width / 2.0;
}

float Wood::getPosHigh()
{
	return Object::asset.getPosition().x + dir * Object::asset.getGlobalBounds().width / 2.0;
}

void Wood::restartClock()
{
	clock.restart();
}