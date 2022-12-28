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
	sprite.setPos(window.getView());
	menuboard.setPos(window.getView());
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

	// Initialize the number of instruction page
	pageIndex = 1;
	pageNum = 4;

	// Background
	Object grassBackground(window, commonAsset[1], 0, 0);
	Object instructionBoard(window, commonAsset[7], 5, 30);
	Object instruct(window, menuTexture[sceneName][pageIndex + 1].first, 13, 33);
	Object page(window, menuTexture[sceneName][pageIndex + 1].second, 102, 130);
	grassBackground.setPos(window.getView());
	instructionBoard.setPos(window.getView());
	instruct.setPos(window.getView());
	page.setPos(window.getView());
	background.push_back(grassBackground);
	background.push_back(instructionBoard);
	background.push_back(instruct);
	background.push_back(page);

	// Button
	SystemButton backButton(window, commonAsset.back(), commonAsset.back(), 0, 0, false);
	buttons.push_back(backButton);
	for (int i = 0; i < 2; ++i)
	{
		SystemButton button(window, menuTexture[sceneName][i].first, menuTexture[sceneName][i].second, (85 + 47 * i), 130, false);
		buttons.push_back(button);
	}
}

Instruction::~Instruction()
{

}

void Instruction::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
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
				else if (i == 1 && pageIndex > 1)
				{
					--pageIndex;
					background.pop_back();
					background.pop_back();
					Object instruct(window, menuTexture[sceneName][pageIndex + 1].first, 13, 33);
					Object page(window, menuTexture[sceneName][pageIndex + 1].second, 102, 130);
					instruct.setPos(window.getView());
					page.setPos(window.getView());
					background.push_back(instruct);
					background.push_back(page);
				}
				else if (i == 2 && pageIndex < pageNum)
				{
					++pageIndex;
					background.pop_back();
					background.pop_back();
					Object instruct(window, menuTexture[sceneName][pageIndex + 1].first, 13, 33);
					Object page(window, menuTexture[sceneName][pageIndex + 1].second, 102, 130);
					instruct.setPos(window.getView());
					page.setPos(window.getView());
					background.push_back(instruct);
					background.push_back(page);
				}
			}
			break;
		}
	}
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
	Object settingsBoard(window, commonAsset[5], 42, 52);
	grassBackground.setPos(window.getView());
	settingsBoard.setPos(window.getView());
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
	Object modeBoard(window, commonAsset[3], 77, 51);
	grassBackground.setPos(window.getView());
	modeBoard.setPos(window.getView());
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
	grassBackground.setPos(window.getView());
	buttonSettingsBoard.setPos(window.getView());
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
