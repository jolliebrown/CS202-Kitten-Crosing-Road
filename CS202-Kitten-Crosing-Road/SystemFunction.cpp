#include "SystemFunction.h"

SystemButton::SystemButton(RenderWindow& window, Texture& unpressed, Texture& pressed, int x_coor, int y_coor) :
	window(window),
	unpressed(window, unpressed, x_coor, y_coor),
	pressed(window, pressed, x_coor, y_coor + 2)
{
}

SystemButton::SystemButton(RenderWindow& window, pair<Texture, Texture>& src, int x_coor, int y_coor) :
	window(window),
	unpressed(window, src.first, x_coor, y_coor),
	pressed(window, src.second, x_coor, y_coor + 2)
{

}

SystemButton::SystemButton(RenderWindow& window, Texture& unpressed, Texture& pressed, int x_coor, int y_coor, bool setCenter) :
	window(window),
	unpressed(window, unpressed, x_coor, y_coor),
	pressed(window, pressed, x_coor, y_coor)
{
	if (setCenter)
	{
		x_coor -= unpressed.getSize().x;
		x_coor /= 2;
		this->pressed.changePos(x_coor, y_coor);
		this->unpressed.changePos(x_coor, y_coor);
	}
}

void SystemButton::draw(const Vector2f& mouse, const bool& isStill)
{
	if (isStill)
		unpressed.draw();
	else
	{
		if (unpressed.isHere(mouse)) pressed.draw();
		else unpressed.draw();
	}
}

FloatingButton::FloatingButton(View& view, RenderWindow& window, Texture& unpressed, Texture& pressed, int x_coor, int y_coor) :
	view(view),
	SystemButton(window, unpressed, pressed, x_coor, y_coor)
{
}

FloatingButton::FloatingButton(View& view, RenderWindow& window, pair<Texture, Texture>& pressed, int x_coor, int y_coor) :
	view(view),
	SystemButton(window, pressed, x_coor, y_coor)
{
}

FloatingButton::FloatingButton(View& view, RenderWindow& window, Texture& unpressed, Texture& pressed, int x_coor, int y_coor, bool setCenter) :
	view(view),
	SystemButton(window, unpressed, pressed, x_coor, y_coor, setCenter)
{
}

void FloatingButton::draw(const Vector2f& mouse, const bool& isStill)
{
	unpressed.setPos(view);
	pressed.setPos(view);
	SystemButton::draw(mouse, isStill);
}

bool SystemButton::isHere(const Vector2f& mouse)
{
	return unpressed.isHere(mouse);
}
InfoScore::InfoScore(RenderWindow& window, int x, int y, int value, vector<Texture>& texture) :
	window(window),
	x(x), y(y), value(value),
	a(window, texture[0], x, y),
	b(window, texture[0], x + 6, y),
	c(window, texture[0], x + 12, y)
{
	update(value, texture);
}

void InfoScore::draw()
{
	setPos(window.getView());
	a.draw();
	b.draw();
	c.draw();
}

void InfoScore::setPos(const View& view)
{
	a.setPos(view);
	b.setPos(view);
	c.setPos(view);
}

void InfoScore::changePos(int _x, int _y)
{
	a.changePos(_x, _y);
	b.changePos(_x + 7, _y);
	c.changePos(_x + 14, _y);
}

void InfoScore::update(int new_value, vector<Texture>& texture)
{
	int a_text = new_value / 100 % 10;
	int b_text = new_value / 10 % 10;
	int c_text = new_value % 10;

	a.setTexture(texture[a_text]);
	b.setTexture(texture[b_text]);
	c.setTexture(texture[c_text]);
}


