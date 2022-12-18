#include "Menu.h"

Button::Button(RenderWindow& mWindow, Texture& texture, int x_coor, int y_coor, bool setCenter) : Object(mWindow, texture, x_coor, y_coor)
{
	if (setCenter)
	{
		x_coor -= texture.getSize().x;
		x_coor /= 2;
		asset.setPosition(x_coor, y_coor);
	}
}

void Button::draw(RenderWindow& window)
{
	window.draw(asset);
}

Scene::Scene(RenderWindow& mWindow) : window(mWindow)
{
	
}

Scene::~Scene()
{
	for (int i = 0; i < buttons.size(); ++i)
		delete buttons[i];
}

void Scene::draw()
{
	for (int i = 0; i < background.size(); ++i)
		window.draw(background[i]);
	for (int i = 0; i < buttons.size(); ++i)
		buttons[i]->draw(window);
}

Menu::Menu(RenderWindow& mWindow) : Scene(mWindow)
{
	// Background
	Sprite sprite(commonAsset[0]);
	background.push_back(sprite);

	sprite = Sprite(commonAsset[1]);
	sprite.setPosition(BaseUnit * 22, BaseUnit * 13);
	sprite.scale(4, 4.5);
	background.push_back(sprite);

	sprite = Sprite(menuAsset[0]);
	sprite.setPosition((BaseUnit * 70 - menuAsset[0].getSize().x) / 2, BaseUnit * 4);
	background.push_back(sprite);

	// Button
	for (int i = 1; i < 7; ++i)
	{
		Button* button = new Button(window, menuAsset[i], BaseUnit * 70, BaseUnit * (15 + 5 * (i - 1)), true);
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
				else if (i == 4)
				{
					Scene* instruction = new Instruction(window);
					scene.push_back(instruction);
					break;
				}
				else if (i == 5)
					event.type = Event::Closed;
				else
				{
					Scene* mode = new Mode(window);
					scene.push_back(mode);
					break;
				}
			}
			if (buttons.size() <= 6)
			{
				Button* button = new Button(window, menuAsset[i + 7], BaseUnit * 70, BaseUnit * (15 + 5 * i), true);
				buttons.push_back(button);
			}
			checkMouse = true;
			break;
		}
	}
	if (!checkMouse && buttons.size() > 6)
	{
		delete buttons.back();
		buttons.pop_back();
	}
}

void Menu::draw()
{
	Scene::draw();
}

Instruction::Instruction(RenderWindow& mWindow) : Scene(mWindow)
{
	// Initialize the number of instruction page
	pageIndex = 1;
	pageNum = 2;

	// Background
	Sprite sprite(commonAsset[0]);
	background.push_back(sprite);

	sprite = Sprite(commonAsset[1]);
	sprite.setPosition(BaseUnit * 2, BaseUnit * 9);
	sprite.scale(10, 5.5);
	background.push_back(sprite);

	sprite = Sprite(instructionAsset[2 * pageIndex - 2]);
	sprite.setPosition((BaseUnit * 70 - instructionAsset[0].getSize().x) / 2, BaseUnit * 11);
	background.push_back(sprite);

	sprite = Sprite(instructionAsset[2 * pageIndex - 1]);
	sprite.setPosition((BaseUnit * 70 - instructionAsset[1].getSize().x) / 2, BaseUnit * 43);
	background.push_back(sprite);

	// Button
	Button* button = new Button(window, commonAsset[2], 0, 0, false);
	buttons.push_back(button);

	button = new Button(window, instructionAsset[6], BaseUnit * 25, BaseUnit * 42, false);
	buttons.push_back(button);

	button = new Button(window, instructionAsset[5], BaseUnit * 41, BaseUnit * 42, false);
	buttons.push_back(button);
}

void Instruction::handleEvent(Event& event, vector<Scene*>& scene, Vector2f mousePosition)
{
	for (int i = 0; i < buttons.size(); ++i)
	{
		if (buttons[i]->getBound().contains(mousePosition))
		{
			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				if (i == 0)
				{
					delete scene.back();
					scene.pop_back();
				}
				else if (i == 1 && pageIndex > 1)
				{
					--pageIndex;
					if (pageIndex == pageNum - 1)
					{
						Button* button = new Button(window, instructionAsset[5], BaseUnit * 41, BaseUnit * 42, false);
						swap(buttons.back(), button);
						delete button;
					}
					if (pageIndex == 1)
					{
						Button* button = new Button(window, instructionAsset[6], BaseUnit * 25, BaseUnit * 42, false);
						swap(buttons[1], button);
						delete button;
					}

					background.pop_back();
					background.pop_back();

					Sprite sprite(instructionAsset[2 * pageIndex - 2]);
					sprite.setPosition((BaseUnit * 70 - instructionAsset[0].getSize().x) / 2, BaseUnit * 11);
					background.push_back(sprite);

					sprite = Sprite(instructionAsset[2 * pageIndex - 1]);
					sprite.setPosition((BaseUnit * 70 - instructionAsset[1].getSize().x) / 2, BaseUnit * 43);
					background.push_back(sprite);
				}
				else if (i == 2 && pageIndex < pageNum)
				{
					++pageIndex;
					if (pageIndex == 2)
					{
						Button* button = new Button(window, instructionAsset[4], BaseUnit * 25, BaseUnit * 42, false);
						swap(buttons[1], button);
						delete button;
					}
					if (pageIndex == pageNum)
					{
						Button* button = new Button(window, instructionAsset[7], BaseUnit * 41, BaseUnit * 42, false);
						swap(buttons.back(), button);
						delete button;
					}

					background.pop_back();
					background.pop_back();

					Sprite sprite(instructionAsset[2]);
					sprite.setPosition((BaseUnit * 70 - instructionAsset[2 * pageIndex - 2].getSize().x) / 2, BaseUnit * 11);
					background.push_back(sprite);

					sprite = Sprite(instructionAsset[3]);
					sprite.setPosition((BaseUnit * 70 - instructionAsset[2 * pageIndex - 1].getSize().x) / 2, BaseUnit * 43);
					background.push_back(sprite);
				}
			}
		}
	}
}

void Instruction::draw()
{
	Scene::draw();
}

Settings::Settings(RenderWindow& mWindow) : Scene(mWindow)
{
	// Background
	Sprite sprite(commonAsset[0]);
	background.push_back(sprite);

	sprite = Sprite(commonAsset[1]);
	sprite.setPosition(BaseUnit * 18.5, BaseUnit * 19);
	sprite.scale(5, 2);
	background.push_back(sprite);

	// Button
	Button* button = new Button(window, commonAsset[2], 0, 0, false);
	buttons.push_back(button);
	for (int i = 0; i < 2; ++i)
	{
		Button* button = new Button(window, settingsAsset[i], BaseUnit * 70, BaseUnit * (22 + 6 * i), true);
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
					delete scene.back();
					scene.pop_back();
					break;
				}
			}
			if (buttons.size() <= 3 && i != 0)
			{
				Button* button = new Button(window, settingsAsset[i + 1], BaseUnit * 70, BaseUnit * (22 + 6 * (i - 1)), true);
				buttons.push_back(button);
			}
			checkMouse = true;
			break;
		}
	}
	if (!checkMouse && buttons.size() > 3)
	{
		delete buttons.back();
		buttons.pop_back();
	}
}

void Settings::draw()
{
	Scene::draw();
}

Mode::Mode(RenderWindow& mWindow) : Scene(mWindow)
{
	// Background
	Sprite sprite(commonAsset[0]);
	background.push_back(sprite);

	sprite = Sprite(commonAsset[1]);
	sprite.setPosition(BaseUnit * 22, BaseUnit * 19);
	sprite.scale(4, 2);
	background.push_back(sprite);

	// Button
	Button* button = new Button(window, commonAsset[2], 0, 0, false);
	buttons.push_back(button);
	for (int i = 0; i < 2; ++i)
	{
		Button* button = new Button(window, modeAsset[i], BaseUnit * 70, BaseUnit * (22 + 6 * i), true);
		buttons.push_back(button);
	}
}

void Mode::handleEvent(Event& event, vector<Scene*>& scene, Vector2f mousePosition)
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
					delete scene.back();
					scene.pop_back();
					break;
				}
			}
			if (buttons.size() <= 3 && i != 0)
			{
				Button* button = new Button(window, modeAsset[i + 1], BaseUnit * 70, BaseUnit * (22 + 6 * (i - 1)), true);
				buttons.push_back(button);
			}
			checkMouse = true;
			break;
		}
	}
	if (!checkMouse && buttons.size() > 3)
	{
		delete buttons.back();
		buttons.pop_back();
	}
}

void Mode::draw()
{
	Scene::draw();
}
