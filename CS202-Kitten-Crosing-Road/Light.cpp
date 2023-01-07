#include "Light.h"

Light::Light(RenderWindow& window, vector<Texture>& texture, int x_coord, int y_coord, int unit) : Object(window, texture[0], x_coord, y_coord, unit)
{
	this->state = 0;
	count[0] = milliseconds(3000);
	count[1] = milliseconds(4000);
	count[2] = milliseconds(10000);
	clock.restart();
	listLight = texture;
	railwaySignal.loadFromFile("Media/SFX/railway_signal.wav");
	_railwaySignal.setBuffer(railwaySignal);
	_railwaySignal.setVolume(25.0f);
}

Light::Light(int state, RenderWindow& window, vector<Texture>& texture, int x_coord, int y_coord, int unit) : Object(window, texture[0], x_coord, y_coord, unit)
{
	this->state = state;
	count[0] = milliseconds(3000);
	count[1] = milliseconds(4000);
	count[2] = milliseconds(10000);
	clock.restart();
	listLight = texture;
}

Light::Light(const Light& light) : Object(light)
{
	state = light.state, clock = light.clock, listLight = light.listLight;
	for (int i = 0; i < 3; ++i) count[i] = light.count[i];
}

void Light::draw()
{
	Object::draw();
	/*if (clock.getElapsedTime().asMilliseconds() > count[state].asMilliseconds()) {
		state++;
		if (state > 2) {
			state = 0;
			clock.restart();
		}
		Object::asset.setTexture(listLight[state]);
	}*/
}

void Light::move() {
	if (clock.getElapsedTime().asMilliseconds() > count[state].asMilliseconds()) {
		state++;
		if (state == 1) {
			_railwaySignal.play();
		}
		if (state > 2) {
			state = 0;
			clock.restart();
		}
		Object::asset.setTexture(listLight[state]);
	}
}

int Light::getState()
{
	return state;
}

float Light::getPos(int dir)
{
	if(dir == 1) return Object::asset.getPosition().x;
	return Object::asset.getPosition().x + 15;
}

void Light::setState(int state)
{
	this->state = state;
	Object::asset.setTexture(listLight[state]);
}

void Light::saveMap(ofstream& os)
{
	os << Object::asset.getPosition().x << ' ' << Object::asset.getPosition().y << '\n';
	os << state << '\n';
}