#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <vector>
#include "Object.h"
#include "other.h"


class InfoScore
{
private:
	Object				a, b, c;
	RenderWindow&		window;
	int					x, y;
	int					value;
public:
	InfoScore(RenderWindow& window, int x, int y, int value, vector<Texture>& texture);
	void		draw();
	void		setPos(const View& view);
	void		changePos(int _x, int _y);
	void		update(int new_value, vector<Texture>& texture);
};

class SystemButton
{
protected:
	Object				unpressed;
	Object				pressed;
	RenderWindow&		window;
public:
	SystemButton(RenderWindow& window, Texture& unpressed, Texture& pressed, int x_coor, int y_coor);
	SystemButton(RenderWindow& window, pair<Texture, Texture>& src, int x_coor, int y_coor);
	SystemButton(RenderWindow& window, Texture& unpressed, Texture& pressed, int x_coor, int y_coor, bool setCenter);
	void				draw(const Vector2f& mouse, const bool& isStill);
	bool				isHere(const Vector2f& mouse);
};

class FloatingButton : public SystemButton
{
private:
	View&				view;
public:
	FloatingButton(View& view, RenderWindow& window, Texture& unpressed, Texture& pressed, int x_coor, int y_coor);
	FloatingButton(View& view, RenderWindow& window, pair<Texture, Texture>& pressed, int x_coor, int y_coor);
	FloatingButton(View& view, RenderWindow& window, Texture& unpressed, Texture& pressed, int x_coor, int y_coor, bool setCenter);
	void				draw(const Vector2f& mouse, const bool& isStill);
};