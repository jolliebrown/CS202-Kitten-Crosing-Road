#include "Menu.h"

const int buttonScaleFactor = 4;

Button::Button(RenderWindow& mWindow, Texture& texture, int x_coor, int y_coor, bool setCenter) : Object(mWindow, texture, x_coor, y_coor)
{
	asset.scale(buttonScaleFactor, buttonScaleFactor);
	if (setCenter)
	{
		x_coor -= texture.getSize().x * buttonScaleFactor;
		x_coor /= 2;
		asset.setPosition(x_coor, y_coor);
	}
}

Scene::Scene(RenderWindow& mWindow) : window(mWindow)
{
	buttons.clear();
}

void Scene::draw()
{
	for (int i = 0; i < background.size(); ++i)
		window.draw(background[i]);
	for (int i = 0; i < buttons.size(); ++i)
		buttons[i]->draw();
}

Menu::Menu(RenderWindow& mWindow) : Scene(mWindow)
{
	Sprite sprite(menuAsset[0]);
	sprite.scale(5, 5);
	background.push_back(sprite);

	sprite = Sprite(menuAsset[1]);
	sprite.setPosition(Vector2f(BaseUnit * 22, BaseUnit * 16));
	sprite.scale(4, 3.5);
	background.push_back(sprite);

	sprite = Sprite(menuAsset[2]);
	sprite.setPosition(Vector2f(BaseUnit * 4, BaseUnit * 4));
	sprite.scale(5, 5);
	background.push_back(sprite);


	for (int i = 3; i < 8; ++i)
	{
		Button* button = new Button(window, menuAsset[i], BaseUnit * 70, BaseUnit * (19.5 + buttonScaleFactor * (i - 3)), true);
		buttons.push_back(button);
	}
}

void Menu::handleEvent(Event& event, vector<Scene*>& scene, Vector2f mousePosition)
{
	bool checkMouse = false;
	for (int i = 0; i < buttons.size(); ++i)
	{
		if (buttons[i]->getBound().contains(mousePosition))
		{
			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				if (i == 2)
				{
					Scene* settings = new Settings(window);
					scene.push_back(settings);
					break;
				}
				else if (i == 3)
				{
					Scene* instruction = new Instruction(window);
					scene.push_back(instruction);
					break;
				}
				else if (i == 4)
					event.type = Event::Closed;
			}
			if (buttons.size() <= 5)
			{
				Button* button = new Button(window, menuAsset[i + 8], BaseUnit * 70, BaseUnit * (19.5 + buttonScaleFactor * i), true);
				buttons.push_back(button);
			}
			checkMouse = true;
			break;
		}
	}
	if (!checkMouse)
	{
		while (buttons.size() > 5)
			buttons.pop_back();
	}
}

void Menu::draw()
{
	Scene::draw();
}

Instruction::Instruction(RenderWindow& mWindow) : Scene(mWindow)
{
	Sprite sprite(instructionAsset[0]);
	sprite.scale(5, 5);
	background.push_back(sprite);

	sprite = Sprite(instructionAsset[1]);
	sprite.setPosition(Vector2f(BaseUnit * 2, BaseUnit * 9));
	sprite.scale(10, 5.5);
	background.push_back(sprite);

	sprite = Sprite(instructionAsset[2]);
	sprite.setPosition(Vector2f(BaseUnit * 4.5, BaseUnit * 15));
	sprite.scale(4, 4);
	background.push_back(sprite);

	Button* button = new Button(window, instructionAsset[4], 0, 0, false);
	buttons.push_back(button);
}

void Instruction::handleEvent(Event& event, vector<Scene*>& scene, Vector2f mousePosition)
{
	if (buttons[0]->getBound().contains(mousePosition))
	{
		if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
		{
			scene.pop_back();
		}
	}
}

void Instruction::draw()
{
	Scene::draw();
}

Settings::Settings(RenderWindow& mWindow) : Scene(mWindow)
{
	Sprite sprite(settingsAsset[0]);
	sprite.scale(5, 5);
	background.push_back(sprite);

	sprite = Sprite(settingsAsset[1]);
	sprite.setPosition(Vector2f(BaseUnit * 22, BaseUnit * 16));
	sprite.scale(4, 3.5);
	background.push_back(sprite);


	Button* button = new Button(window, settingsAsset[2], 0, 0, false);
	buttons.push_back(button);
	for (int i = 3; i < 5; ++i)
	{
		Button* button = new Button(window, settingsAsset[i], BaseUnit * 70, BaseUnit * (19.5 + buttonScaleFactor * (i - 2)), true);
		buttons.push_back(button);
	}
}

void Settings::handleEvent(Event& event, vector<Scene*>& scene, Vector2f mousePosition)
{
	bool checkMouse = false;
	for (int i = 0; i < buttons.size(); ++i)
	{
		if (buttons[i]->getBound().contains(mousePosition))
		{
			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				if (i == 0)
				{
					scene.pop_back();
					break;
				}
			}
			if (buttons.size() <= 3 && i != 0)
			{
				Button* button = new Button(window, settingsAsset[i + 4], BaseUnit * 70, BaseUnit * (19.5 + buttonScaleFactor * i), true);
				buttons.push_back(button);
			}
			checkMouse = true;
			break;
		}
	}
	if (!checkMouse)
	{
		while (buttons.size() > 3)
			buttons.pop_back();
	}
}

void Settings::draw()
{
	Scene::draw();
}
