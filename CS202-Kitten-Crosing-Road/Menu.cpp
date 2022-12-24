#include "Menu.h"

Scene::Scene(RenderWindow& mWindow) : window(mWindow)
{
	sceneName = MenuList::Menu;
}

Scene::~Scene()
{

}

void Scene::draw(const Vector2f& mouse)
{
	// draw 
	for (int i = 0; i < background.size(); ++i)
	{
		background[i].draw();
	}
	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i].draw(mouse, false);
	}
}


Menu::Menu(RenderWindow& mWindow) : Scene(mWindow)
{
	sceneName = MenuList::Menu;

	// Background
	Object sprite(window, commonAsset[0], 0, 0);
	Object menuboard(window, commonAsset[2], 59, 40);
	sprite.setPos(mWindow.getView());
	menuboard.setPos(mWindow.getView());
	background.push_back(sprite);
	background.push_back(menuboard);

	// Button
	for (int i = 0; i < menuTexture[sceneName].size(); ++i)
	{
		SystemButton button(window, menuTexture[sceneName][i].first, menuTexture[sceneName][i].second,  224, (50 + 17 * i), true);
		buttons.push_back(button);
	}
}

Menu::~Menu()
{

}

void Menu::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
{
	for (int i = 0; i < buttons.size(); ++i)
	{
		if (buttons[i].isHere(mousePosition))
		{
			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				if (i == 2)
				{
					Scene* settings = new Settings(window);
					scene.push_back(settings);
				}
				else if (i == 3)
				{
					Scene* instruction = new Instruction(window);
					scene.push_back(instruction);
				}
				else if (i == 5)
				{
					const_cast<Event&>(event).type = Event::Closed;
				}
				else
				{
					Scene* mode = new Mode(window);
					scene.push_back(mode);
				}
			}
			break;
		}
	}
}

void Menu::draw(const Vector2f& mouse)
{
	Scene::draw(mouse);
}

Instruction::Instruction(RenderWindow& mWindow) : Scene(mWindow)
{
	sceneName = MenuList::Instruction;

	// Background
	Object sprite(window, commonAsset[0], 0, 0);
	Object menuboard(window, commonAsset[1], 2, 9);

	background.push_back(sprite);
	background.push_back(sprite);
	// Initialize the number of instruction page
	pageIndex = 1;
	pageNum = 2;

	// Background
	//Sprite sprite(commonAsset[0]);
	//background.push_back(sprite);

	//sprite = Sprite(commonAsset[1]);
	//sprite.setPosition(BaseUnit * 2, BaseUnit * 9);
	//sprite.scale(10, 5.5);
	//background.push_back(sprite);

	//sprite = Sprite(instructionAsset[2 * pageIndex - 2]);
	//sprite.setPosition((BaseUnit * 70 - instructionAsset[0].getSize().x) / 2, BaseUnit * 11);
	//background.push_back(sprite);

	//sprite = Sprite(instructionAsset[2 * pageIndex - 1]);
	//sprite.setPosition((BaseUnit * 70 - instructionAsset[1].getSize().x) / 2, BaseUnit * 43);
	//background.push_back(sprite);

	// SystemButton
	for (int i = 0; i < menuTexture[sceneName].size(); i++)
	{

	}
	/*SystemButton* button = new SystemButton(window, commonAsset[2], 0, 0, false);
	buttons.push_back(button);

	button = new SystemButton(window, instructionAsset[6], BaseUnit * 25, BaseUnit * 42, false);
	buttons.push_back(button);

	button = new SystemButton(window, instructionAsset[5], BaseUnit * 41, BaseUnit * 42, false);
	buttons.push_back(button);*/
}

Instruction::~Instruction()
{

}

void Instruction::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
{
	/*for (int i = 0; i < buttons.size(); ++i)
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
						SystemButton* button = new SystemButton(window, instructionAsset[5], BaseUnit * 41, BaseUnit * 42, false);
						swap(buttons.back(), button);
						delete button;
					}
					if (pageIndex == 1)
					{
						SystemButton* button = new SystemButton(window, instructionAsset[6], BaseUnit * 25, BaseUnit * 42, false);
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
						SystemButton* button = new SystemButton(window, instructionAsset[4], BaseUnit * 25, BaseUnit * 42, false);
						swap(buttons[1], button);
						delete button;
					}
					if (pageIndex == pageNum)
					{
						SystemButton* button = new SystemButton(window, instructionAsset[7], BaseUnit * 41, BaseUnit * 42, false);
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
	}*/
}

void Instruction::draw(const Vector2f& mouse)
{
	Scene::draw(mouse);
}

Settings::Settings(RenderWindow& mWindow) : Scene(mWindow)
{
	sceneName = MenuList::Settings;

	// Background
	//Sprite sprite(commonAsset[0]);
	//background.push_back(sprite);

	//sprite = Sprite(commonAsset[1]);
	//sprite.setPosition(BaseUnit * 18.5, BaseUnit * 19);
	//sprite.scale(5, 2);
	//background.push_back(sprite);

	//// SystemButton
	//SystemButton* button = new SystemButton(window, commonAsset[2], 0, 0, false);
	//buttons.push_back(button);
	//for (int i = 0; i < 2; ++i)
	//{
	//	SystemButton* button = new SystemButton(window, settingsAsset[i], BaseUnit * 70, BaseUnit * (22 + 6 * i), true);
	//	buttons.push_back(button);
	//}
}

Settings::~Settings()
{

}

void Settings::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
{
	/*bool checkMouse = false;
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
				else if (i == 2)
				{
					Scene* buttonSettings = new ButtonSettings(window);
					scene.push_back(buttonSettings);
					break;
				}
			}
			if (buttons.size() <= 3 && i != 0)
			{
				SystemButton* button = new SystemButton(window, settingsAsset[i + 1], BaseUnit * 70, BaseUnit * (22 + 6 * (i - 1)), true);
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
	}*/
}

void Settings::draw(const Vector2f& mouse)
{
	Scene::draw(mouse);
}

Mode::Mode(RenderWindow& mWindow) : Scene(mWindow)
{
	sceneName = MenuList::Mode;

	//// Background
	//Sprite sprite(commonAsset[0]);
	//background.push_back(sprite);

	//sprite = Sprite(commonAsset[1]);
	//sprite.setPosition(BaseUnit * 22, BaseUnit * 19);
	//sprite.scale(4, 2);
	//background.push_back(sprite);

	//// SystemButton
	//SystemButton* button = new SystemButton(window, commonAsset[2], 0, 0, false);
	//buttons.push_back(button);
	//for (int i = 0; i < 2; ++i)
	//{
	//	SystemButton* button = new SystemButton(window, modeAsset[i], BaseUnit * 70, BaseUnit * (22 + 6 * i), true);
	//	buttons.push_back(button);
	//}
}

Mode::~Mode()
{

}

void Mode::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
{
	/*bool checkMouse = false;
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
				SystemButton* button = new SystemButton(window, modeAsset[i + 1], BaseUnit * 70, BaseUnit * (22 + 6 * (i - 1)), true);
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
	}*/
}

void Mode::draw(const Vector2f& mouse)
{
	Scene::draw(mouse);
}

ButtonSettings::ButtonSettings(RenderWindow& mWindow) : Scene(mWindow)
{
	//sceneName = MenuList::ButtonSettings;

	//// Background
	//Sprite sprite(commonAsset[0]);
	//background.push_back(sprite);

	//sprite = Sprite(commonAsset[1]);
	//sprite.setPosition(BaseUnit * 17, BaseUnit * 16);
	//sprite.scale(5.5, 4);
	//background.push_back(sprite);

	//// SystemButton
	//SystemButton* button = new SystemButton(window, commonAsset[2], 0, 0, false);
	//buttons.push_back(button);
	//for (int i = 0; i < 4; ++i)
	//{
	//	SystemButton* button = new SystemButton(window, buttonSettings_Asset[i], BaseUnit * 70, BaseUnit * (20 + 6 * i), true);
	//	buttons.push_back(button);
	//}
}

ButtonSettings::~ButtonSettings()
{

}

void ButtonSettings::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
{
	/*bool checkMouse = false;
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
			if (buttons.size() <= 5 && i != 0)
			{
				SystemButton* button = new SystemButton(window, buttonSettings_Asset[i + 3], BaseUnit * 70, BaseUnit * (20 + 6 * (i - 1)), true);
				buttons.push_back(button);
			}
			checkMouse = true;
			break;
		}
	}
	if (!checkMouse && buttons.size() > 5)
	{
		delete buttons.back();
		buttons.pop_back();
	}*/
}

void ButtonSettings::draw(const Vector2f& mouse)
{
	Scene::draw(mouse);
}
