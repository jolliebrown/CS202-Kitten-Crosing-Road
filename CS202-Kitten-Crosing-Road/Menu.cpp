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
	onePicLoad(asset, "Media/Menu/Menu.png");
	onePicLoad(asset, "Media/Menu/CONTINUE.png");
	onePicLoad(asset, "Media/Menu/PLAY.png");
	onePicLoad(asset, "Media/Menu/SETTINGS.png");
	onePicLoad(asset, "Media/Menu/INSTRUCTION.png");
	onePicLoad(asset, "Media/Menu/QUIT.png");
	onePicLoad(asset, "Media/Menu/CONTINUE_here.png");
	onePicLoad(asset, "Media/Menu/PLAY_here.png");
	onePicLoad(asset, "Media/Menu/SETTINGS_here.png");
	onePicLoad(asset, "Media/Menu/INSTRUCTION_here.png");
	onePicLoad(asset, "Media/Menu/QUIT_here.png");

	Sprite sprite(asset[0]);
	sprite.setPosition(Vector2f(BaseUnit * 31, BaseUnit * 19));
	background.push_back(sprite);
	for (int i = 1; i < 6; ++i)
	{
		Button button(window, asset[i], BaseUnit * 32, BaseUnit * (19.5 + i));
		buttons.push_back(button);
	}
	loadCursor();
}

void Menu::handleEvent(Event& event, vector<Menu*>& mMenu)
{
	
}

void Menu::draw()
{
	
}

void Menu::loadCursor()
{
	Image image;
	image.loadFromFile("Media/Menu/normalMouse.png");
	Cursor* cursor;
	cursor = new Cursor;
	cursor->loadFromPixels(image.getPixelsPtr(), Vector2u(16, 16), Vector2u(0, 0));
	cursorTexture.push_back(cursor);
	cursor = new Cursor;
	image.loadFromFile("Media/Menu/pointingMouse.png");
	cursor->loadFromPixels(image.getPixelsPtr(), Vector2u(16, 16), Vector2u(0, 0));
	cursorTexture.push_back(cursor);
}

void Menu::loadAsset()
{

}