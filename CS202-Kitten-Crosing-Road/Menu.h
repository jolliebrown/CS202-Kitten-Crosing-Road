#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Object.h"

class Button : public Object {
public:
	Button(RenderWindow& mWindow, Texture& texture, int x_coor, int y_coor);
	
	Sprite getSprite();
};

class Menu : public ListTextures {
public:
	Menu(RenderWindow& Window);

	virtual void handleEvent(Event& event, vector<Menu*>& mMenu);
	virtual void draw();
	void loadCursor();
	virtual void loadAsset();
protected:
	RenderWindow& window;
	vector<Cursor*> cursorTexture;
	vector<Button> buttons;
	vector<Texture> asset;
	vector<Sprite> background;
};

class Instruction : public Menu {
public:
	Instruction(RenderWindow& mWindow);

	void handleEvent(Event& event, vector<Menu*>& mMenu) override;
	void draw() override;
};