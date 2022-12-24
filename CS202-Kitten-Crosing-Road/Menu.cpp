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
	Object grassBackground(window, commonAsset[1], 0, 0);
	Object settingsBoard(window, commonAsset[5], 51.5, 55);
	grassBackground.setPos(mWindow.getView());
	settingsBoard.setPos(mWindow.getView());
	background.push_back(grassBackground);
	background.push_back(settingsBoard);

	// Button
	SystemButton backButton(window, commonAsset.back(), commonAsset.back(), 0, 0, false);
	buttons.push_back(backButton);
	for (int i = 0; i < menuTexture[sceneName].size(); ++i)
	{
		SystemButton button(window, menuTexture[sceneName][i].first, menuTexture[sceneName][i].second, 224, (65 + 25 * i), true);
		buttons.push_back(button);
	}
}

Settings::~Settings()
{

}

void Settings::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
{
	for (int i = 0; i < buttons.size(); ++i)
	{
		if (buttons[i].isHere(mousePosition))
		{
			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				if (i == 0)
				{
					scene.pop_back();
				}
				else if (i == 2)
				{
					Scene* buttonSettings = new ButtonSettings(window);
					scene.push_back(buttonSettings);
				}
			}
			break;
		}
	}
}

void Settings::draw(const Vector2f& mouse)
{
	Scene::draw(mouse);
}

Mode::Mode(RenderWindow& mWindow) : Scene(mWindow)
{
	sceneName = MenuList::Mode;

	// Background
	Object grassBackground(window, commonAsset[1], 0, 0);
	Object modeBoard(window, commonAsset[3], 76, 56);
	grassBackground.setPos(mWindow.getView());
	modeBoard.setPos(mWindow.getView());
	background.push_back(grassBackground);
	background.push_back(modeBoard);

	// Button
	SystemButton backButton(window, commonAsset.back(), commonAsset.back(), 0, 0, false);
	buttons.push_back(backButton);
	for (int i = 0; i < menuTexture[sceneName].size(); ++i)
	{
		SystemButton button(window, menuTexture[sceneName][i].first, menuTexture[sceneName][i].second, 224, (65 + 25 * i), true);
		buttons.push_back(button);
	}
}

Mode::~Mode()
{

}

void Mode::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
{
	for (int i = 0; i < buttons.size(); ++i)
	{
		if (buttons[i].isHere(mousePosition))
		{
			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				if (i == 0)
				{
					scene.pop_back();
				}
			}
			break;
		}
	}
}

void Mode::draw(const Vector2f& mouse)
{
	Scene::draw(mouse);
}

ButtonSettings::ButtonSettings(RenderWindow& mWindow) : Scene(mWindow)
{
	sceneName = MenuList::ButtonSettings;

	// Background
	Object grassBackground(window, commonAsset[1], 0, 0);
	Object buttonSettingsBoard(window, commonAsset[6], 42, 37);
	grassBackground.setPos(mWindow.getView());
	buttonSettingsBoard.setPos(mWindow.getView());
	background.push_back(grassBackground);
	background.push_back(buttonSettingsBoard);

	// Button
	SystemButton backButton(window, commonAsset.back(), commonAsset.back(), 0, 0, false);
	buttons.push_back(backButton);
	for (int i = 0; i < menuTexture[sceneName].size(); ++i)
	{
		SystemButton button(window, menuTexture[sceneName][i].first, menuTexture[sceneName][i].second, 224, (50 + 25 * i), true);
		buttons.push_back(button);
	}
}

ButtonSettings::~ButtonSettings()
{

}

void ButtonSettings::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
{
	for (int i = 0; i < buttons.size(); ++i)
	{
		if (buttons[i].isHere(mousePosition))
		{
			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				if (i == 0)
				{
					scene.pop_back();
				}
			}
			break;
		}
	}
}

void ButtonSettings::draw(const Vector2f& mouse)
{
	Scene::draw(mouse);
}
