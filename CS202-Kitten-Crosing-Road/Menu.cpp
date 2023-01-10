#include "Menu.h"
#include "SFML/Audio.hpp"

static Music music[2] = {};

Scene::Scene(RenderWindow& mWindow) : window(mWindow)
{
	sceneName = MenuList::Menu;

	// Initial moving buttons for player are arrow buttons
	for (int i = 71; i < 75; ++i)
	{
		movingButtons.push_back((Keyboard::Key)i);
	}
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

int Scene::center(const Texture& texture) const
{
	return (224 - texture.getSize().x) / 2;
}

vector<Keyboard::Key> Scene::getKeyboard() const
{
	return movingButtons;
}


Menu::Menu(RenderWindow& mWindow) : Scene(mWindow)
{
	sceneName = MenuList::Menu;

	// Background
	Object sprite(window, commonAsset[0], 0, 0);
	Object menuboard(window, commonAsset[2], center(commonAsset[2]), 40);
	sprite.setPos(window.getView());
	menuboard.setPos(window.getView());
	background.push_back(sprite);
	background.push_back(menuboard);

	// Button
	for (int i = 0; i < menuTexture[sceneName].size(); ++i)
	{
		SystemButton button(window, menuTexture[sceneName][i].first, menuTexture[sceneName][i].second, 224, (50 + 17 * i), true);
		buttons.push_back(button);
	}
}

Menu::~Menu()
{

}

int Menu::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
{
	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		for (int i = 0; i < buttons.size(); ++i)
		{
			if (buttons[i].isHere(mousePosition))
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
					ButtonList currentButton;
					if (i == 0)
					{
						currentButton = ButtonList::Continue;
						Scene* mode = new Mode(window, currentButton);
						scene.push_back(mode);
					}
					else if (i == 1)
					{
						currentButton = ButtonList::Play;
						Scene* mode = new Mode(window, currentButton);
						scene.push_back(mode);
					}
					else if (i == 4)
					{
						currentButton = ButtonList::Leaderboard;
						Scene* mode = new Mode(window, currentButton);
						scene.push_back(mode);
					}
					return -(i + 1);
				}
				break;
			}
		}
	}
	return 0;
}

void Menu::draw(const Vector2f& mouse)
{
	Scene::draw(mouse);
}

Mode::Mode(RenderWindow& mWindow, ButtonList PreviousButton) : Scene(mWindow), previousButton(PreviousButton)
{
	sceneName = MenuList::Mode;

	// Background
	Object grassBackground(window, commonAsset[1], 0, 0);
	Object modeBoard(window, commonAsset[3], center(commonAsset[3]), 51);
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

int Mode::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
{
	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		for (int i = 0; i < buttons.size(); ++i)
		{
			if (buttons[i].isHere(mousePosition))
			{
				if (i == 0)
				{
					scene.pop_back();
				}
				else if (i == 1)
				{
					Scene* classic = new Classic(window);
					scene.push_back(classic);
					return 1;
				}
				else if (i == 2)
				{
					scene.pop_back();
					return 2;
				}
				break;
			}
		}
	}
	return 0;
}

void Mode::draw(const Vector2f& mouse)
{
	Scene::draw(mouse);
}

Classic::Classic(RenderWindow& mWindow) : Scene(mWindow)
{
	sceneName = MenuList::Classic;

	// Initialize the number of level page
	pageIndex = 1;
	pageNum = 2;

	// Background
	Object grassBackground(window, commonAsset[1], 0, 0);
	Object settingsBoard(window, commonAsset[4], center(commonAsset[4]), 30);
	Object page(window, menuTexture[sceneName][pageIndex + 11].first, center(menuTexture[sceneName][pageIndex + 11].first), 136);
	grassBackground.setPos(window.getView());
	settingsBoard.setPos(window.getView());
	page.setPos(window.getView());
	background.push_back(grassBackground);
	background.push_back(settingsBoard);
	background.push_back(page);

	// Button
	SystemButton backButton(window, commonAsset.back(), commonAsset.back(), 0, 0, false);
	buttons.push_back(backButton);
	for (int i = 0; i < 2; ++i)
	{
		SystemButton button(window, menuTexture[sceneName][i].first, menuTexture[sceneName][i].second, (85 + 47 * i), 135, false);
		buttons.push_back(button);
	}
	for (int i = 2; i < 7; ++i)
	{
		SystemButton button(window, menuTexture[sceneName][i].first, menuTexture[sceneName][i].second, 224, (38 + 19 * (i - 2)), true);
		buttons.push_back(button);
	}
}

Classic::~Classic()
{

}

int Classic::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
{
	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		for (int i = 0; i < buttons.size(); ++i)
		{
			if (buttons[i].isHere(mousePosition))
			{
				if (i == 0)
				{
					scene.pop_back();
				}
				else
				{
					if (i == 1 && pageIndex > 1)
					{
						--pageIndex;
					}
					else if (i == 2 && pageIndex < pageNum)
					{
						++pageIndex;
					}
					background.pop_back();
					while (buttons.size() > 3)
					{
						buttons.pop_back();
					}

					// New page index
					Object page(window, menuTexture[sceneName][pageIndex + 11].first, center(menuTexture[sceneName][pageIndex + 11].first), 136);
					page.setPos(window.getView());
					background.push_back(page);

					// Levels in the new page
					for (int j = 5 * (pageIndex - 1) + 2; j < 5 * pageIndex + 2; ++j)
					{
						SystemButton button(window, menuTexture[sceneName][j].first, menuTexture[sceneName][j].second, 224, (38 + 19 * (j - (5 * (pageIndex - 1) + 2))), true);
						buttons.push_back(button);
					}
				}
				break;
			}
		}
	}
	return 0;
}

void Classic::draw(const Vector2f& mouse)
{
	Scene::draw(mouse);
}

Settings::Settings(RenderWindow& mWindow) : Scene(mWindow)
{
	sceneName = MenuList::Settings;

	// Background
	Object grassBackground(window, commonAsset[1], 0, 0);
	Object settingsBoard(window, commonAsset[5], center(commonAsset[5]), 52);
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

int Settings::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
{
	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		for (int i = 0; i < buttons.size(); ++i)
		{
			if (buttons[i].isHere(mousePosition))
			{
				if (i == 0)
				{
					scene.pop_back();
				}
				else if (i == 1)
				{
					Scene* soundSettings = new SoundSettings(window);
					scene.push_back(soundSettings);
				}
				else if (i == 2)
				{
					Scene* buttonSettings = new ButtonSettings(window);
					scene.push_back(buttonSettings);
				}
				break;
			}
		}
	}
	return 0;
}

void Settings::draw(const Vector2f& mouse)
{
	Scene::draw(mouse);
}

SoundSettings::SoundSettings(RenderWindow& mWindow) : Scene(mWindow)
{
	sceneName = MenuList::SoundSettings;

	// Background
	Object grassBackground(window, commonAsset[1], 0, 0);
	Object soundBoard(window, commonAsset[6], center(commonAsset[6]), 52);
	Object bgmText(window, menuTexture[sceneName][2].first, 62, 65);
	Object sfxText(window, menuTexture[sceneName][2].second, 62, 90);
	grassBackground.setPos(window.getView());
	soundBoard.setPos(window.getView());
	bgmText.setPos(window.getView());
	sfxText.setPos(window.getView());
	background.push_back(grassBackground);
	background.push_back(soundBoard);
	background.push_back(bgmText);
	background.push_back(sfxText);

	// Sound Bar
	soundBar.resize(2);
	for (int i = 0; i < 2; ++i)
	{
		Object blankBar(window, menuTexture[sceneName][3].first, 135, (64 + 25 * i));
		blankBar.setPos(window.getView());
		soundBar[i].push_back(blankBar);
		for (float f = 0; f < music[i].getVolume(); f += 25)
		{
			Object currentSound(window, menuTexture[sceneName][3].second, (135 + f / 5), (64 + 25 * i));
			currentSound.setPos(window.getView());
			soundBar[i].push_back(currentSound);
		}
	}

	// Button
	SystemButton backButton(window, commonAsset.back(), commonAsset.back(), 0, 0, false);
	buttons.push_back(backButton);
	for (int i = 0; i < 2; ++i)
	{
		SystemButton bgmButton(window, menuTexture[sceneName][i].first, menuTexture[sceneName][i].second, (122 + 37 * i), (68 - 2 * i), false);
		SystemButton sfxButton(window, menuTexture[sceneName][i].first, menuTexture[sceneName][i].second, (122 + 37 * i), (93 - 2 * i), false);
		buttons.push_back(bgmButton);
		buttons.push_back(sfxButton);
	}
}

SoundSettings::~SoundSettings()
{

}

int SoundSettings::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
{
	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		for (int i = 0; i < buttons.size(); ++i)
		{
			if (buttons[i].isHere(mousePosition))
			{
				if (i == 0)
				{
					scene.pop_back();
				}
				else if (i < buttons.size() / 2 + 1 && music[i - 1].getVolume() > 0)
				{
					// Press the decrease-sound button
					soundBar[i - 1].pop_back();
					music[i - 1].setVolume(music[i - 1].getVolume() - 25);
				}
				else if (i > buttons.size() / 2 && music[i - 1 - buttons.size() / 2].getVolume() < 100)
				{
					// Press the increase-sound button
					Object currentSound(window, menuTexture[sceneName][3].second, (135 + music[i - 1 - buttons.size() / 2].getVolume() / 5), (64 + 25 * (i - 1 - buttons.size() / 2)));
					currentSound.setPos(window.getView());
					soundBar[i - 1 - buttons.size() / 2].push_back(currentSound);
					music[i - 1 - buttons.size() / 2].setVolume(music[i - 1 - buttons.size() / 2].getVolume() + 25);
				}
				break;
			}
		}
	}
	return 0;
}

void SoundSettings::draw(const Vector2f& mouse)
{
	Scene::draw(mouse);
	for (int i = 0; i < soundBar.size(); ++i)
	{
		for (int j = 0; j < soundBar[i].size(); ++j)
			soundBar[i][j].draw();
	}
}

ButtonSettings::ButtonSettings(RenderWindow& mWindow) : Scene(mWindow)
{
	sceneName = MenuList::ButtonSettings;
	buttonPressed = -1;

	// Background
	Object grassBackground(window, commonAsset[1], 0, 0);
	Object buttonSettingsBoard(window, commonAsset[7], center(commonAsset[7]), 37);
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

	for (int i = 0; i < 36; i++)
	{
		Keyboard::Key tmp = (Keyboard::Key)i;
		if (key_text[tmp].loadFromFile("Media/Scene/ButtonSettings/Keyboards/" + to_string(i) + ".png"))
		{
			key[tmp].setTexture(key_text[tmp]);
			key_pressed[tmp] = 0;
			key[tmp].setPosition(center(key_text[tmp]), (160 - key_text[tmp].getSize().y) / 2);
		}
	}
	for (int i = 46; i < 59; i++)
	{
		Keyboard::Key tmp = (Keyboard::Key)i;
		if (key_text[tmp].loadFromFile("Media/Scene/ButtonSettings/Keyboards/" + to_string(i) + ".png"))
		{
			key[tmp].setTexture(key_text[tmp]);
			key_pressed[tmp] = 0;
			key[tmp].setPosition(center(key_text[tmp]), (160 - key_text[tmp].getSize().y) / 2);
		}
	}
	for (int i = 71; i < 75; ++i)
	{
		Keyboard::Key tmp = (Keyboard::Key)i;
		if (key_text[tmp].loadFromFile("Media/Scene/ButtonSettings/Keyboards/" + to_string(i) + ".png"))
		{
			key[tmp].setTexture(key_text[tmp]);
			key_pressed[tmp] = 0;
			key[tmp].setPosition(center(key_text[tmp]), (160 - key_text[tmp].getSize().y) / 2);
		}
	}
}

ButtonSettings::~ButtonSettings()
{

}

int ButtonSettings::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
{
	if (buttonPressed == -1 && event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		for (int i = 0; i < buttons.size(); ++i)
		{
			if (buttons[i].isHere(mousePosition))
			{
				if (i == 0)
				{
					scene.pop_back();
					return -100;
				}
				else
				{
					
						buttonPressed = i - 1;
						key_pressed[movingButtons[buttonPressed]] = 0;
						while (buttons.size() > 1)
							buttons.pop_back();
						for (int j = 0; j < menuTexture[sceneName].size(); ++j)
						{
							Object button(window, menuTexture[sceneName][j].first, center(menuTexture[sceneName][j].first), (50 + 25 * j));
							background.push_back(button);
						}
						Object button(window, menuTexture[sceneName][i - 1].second, center(menuTexture[sceneName][i - 1].second), (50 + 25 * (i - 1)));
						background.push_back(button);
				}
				break;
			}
		}
	}
	else if (buttonPressed != -1)
	{
		if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && buttons[0].isHere(mousePosition))
		{
			scene.pop_back();
		}
		else if (event.type == Event::KeyReleased)
		{
			bool check = true;
			for (int j = 0; j < 4; j++)
			{
				if (j == buttonPressed)
					continue;
				if (movingButtons[j] == event.key.code)
				{
					check = false;
					break;
				}
			}
			if (check)
			{
				key_pressed[movingButtons[buttonPressed]] = 0;
				movingButtons[buttonPressed] = event.key.code;
				recent = movingButtons[buttonPressed];
				buttonPressed = -1;
				for (int i = 0; i < 5; ++i)
				{
					background.pop_back();
				}
				for (int i = 0; i < menuTexture[sceneName].size(); ++i)
				{
					SystemButton button(window, menuTexture[sceneName][i].first, menuTexture[sceneName][i].second, 224, (50 + 25 * i), true);
					buttons.push_back(button);
				}
				return recent + 10;
			}
			else
			{
				// duplicate
				buttonPressed = -1;
				for (int i = 0; i < 5; ++i)
				{
					background.pop_back();
				}
				for (int i = 0; i < menuTexture[sceneName].size(); ++i)
				{
					SystemButton button(window, menuTexture[sceneName][i].first, menuTexture[sceneName][i].second, 224, (50 + 25 * i), true);
					buttons.push_back(button);
				}
				return 0;
			}
		}
	}
	return 0;
}

void ButtonSettings::draw(const Vector2f& mouse)
{
	Scene::draw(mouse);
	if (buttonPressed != -1 && key_pressed[movingButtons[buttonPressed]] < KeyDisplay)
	{
		window.draw(key[movingButtons[buttonPressed]]);
		key_pressed[movingButtons[buttonPressed]]++;
	}
	else if (buttonPressed == -1 && recent != -1 && key_pressed[(Keyboard::Key)recent] < KeyDisplay)
	{
		window.draw(key[(Keyboard::Key)recent]);
		key_pressed[(Keyboard::Key)recent]++;
	}
}

Instruction::Instruction(RenderWindow& mWindow) : Scene(mWindow)
{
	sceneName = MenuList::Instruction;

	// Initialize the number of instruction page
	pageIndex = 1;
	pageNum = 4;

	// Background
	Object grassBackground(window, commonAsset[1], 0, 0);
	Object instructionBoard(window, commonAsset[8], center(commonAsset[8]), 30);
	Object instruct(window, menuTexture[sceneName][pageIndex + 1].first, center(menuTexture[sceneName][pageIndex + 1].first), 34);
	Object page(window, menuTexture[sceneName][pageIndex + 1].second, center(menuTexture[sceneName][pageIndex + 1].second), 126);
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
		SystemButton button(window, menuTexture[sceneName][i].first, menuTexture[sceneName][i].second, (85 + 47 * i), 125, false);
		buttons.push_back(button);
	}
}

Instruction::~Instruction()
{

}

int Instruction::handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition)
{
	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		for (int i = 0; i < buttons.size(); ++i)
		{
			if (buttons[i].isHere(mousePosition))
			{
				if (i == 0)
				{
					scene.pop_back();
				}
				else
				{
					if (i == 1 && pageIndex > 1)
					{
						--pageIndex;
					}
					else if (i == 2 && pageIndex < pageNum)
					{
						++pageIndex;
					}
					background.pop_back();
					background.pop_back();
					Object instruct(window, menuTexture[sceneName][pageIndex + 1].first, center(menuTexture[sceneName][pageIndex + 1].first), 34);
					Object page(window, menuTexture[sceneName][pageIndex + 1].second, center(menuTexture[sceneName][pageIndex + 1].second), 126);
					instruct.setPos(window.getView());
					page.setPos(window.getView());
					background.push_back(instruct);
					background.push_back(page);
				}
				break;
			}
		}
	}
	return 0;
}

void Instruction::draw(const Vector2f& mouse)
{
	Scene::draw(mouse);
}