#include "Menu.h"

Button::Button(RenderWindow& mWindow, Texture& texture, int x_coor, int y_coor) : Object(mWindow, texture, x_coor, y_coor)
{

}

Sprite Button::getSprite()
{
	return asset;
}

Menu::Menu(RenderWindow& mWindow) : window(mWindow)
{
	
}

void Menu::handleEvent(Event& event, vector<Menu*>& mMenu)
{
	
}

void Menu::draw()
{
	
}

void Menu::loadCursor()
{
	
}

void Menu::loadAsset()
{

}