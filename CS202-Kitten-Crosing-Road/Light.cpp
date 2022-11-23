#include "Light.h"

Light::Light(int state, RenderWindow& window, vector<Texture>& texture, int x_coord, int y_coord, int unit) : Object(window, texture[0], x_coord, y_coord, unit)
{
	this->state = state;
	count[0] = milliseconds(5000);
	count[1] = milliseconds(7000);
	count[2] = milliseconds(12000);
	clock.restart();
	listLight = texture;
}

void Light::draw()
{
	Object::draw();
	if (clock.getElapsedTime().asMilliseconds() > count[state].asMilliseconds()) {
		state++;
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

float Light::getPos()
{
	return Object::asset.getPosition().x;
}