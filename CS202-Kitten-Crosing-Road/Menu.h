#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <map>

#include "SystemFunction.h"

const int KeyDisplay = 1000;



enum class ButtonList
{
	Continue,
	Play,
	Leaderboard
};

class Scene : public ListTextures {
public:
	Scene(RenderWindow& mWindow);
	virtual ~Scene();

	virtual int				handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition) = 0;
	virtual void			draw(const Vector2f& mouse);
	void					getName() const;
	int						center(const Texture& texture) const;
	vector<Keyboard::Key>	getKeyboard() const;
protected:
	RenderWindow& window;
	vector<SystemButton>	buttons;
	vector<Object>			background;
	MenuList				sceneName;
	vector<Keyboard::Key>	movingButtons;
};

class Menu : public Scene {
public:
	Menu(RenderWindow& mWindow);
	~Menu() override;

	int handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition) override;
	void draw(const Vector2f& mouse) override;
};

class Mode : public Scene {
public:
	Mode(RenderWindow& mWindow, ButtonList PreviousButton);
	~Mode() override;

	int handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition) override;
	void draw(const Vector2f& mouse) override;
private:
	ButtonList previousButton;
};

class Settings : public Scene {
public:
	Settings(RenderWindow& mWindow);
	~Settings() override;

	int handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition) override;
	void draw(const Vector2f& mouse) override;
};

class SoundSettings : public Scene {
public:
	SoundSettings(RenderWindow& mWindow);
	~SoundSettings() override;

	int handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition) override;
	void draw(const Vector2f& mouse) override;
private:
	vector<vector<Object>> soundBar;
};

class ButtonSettings : public Scene {
public:
	ButtonSettings(RenderWindow& mWindow);
	~ButtonSettings() override;

	int handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition) override;
	void draw(const Vector2f& mouse) override;
private:
	map<Keyboard::Key, Texture> key_text;
	map<Keyboard::Key, Sprite> key;
	map<Keyboard::Key, int> key_pressed;
	int buttonPressed, recent = -1;
};

class Instruction : public Scene {
public:
	Instruction(RenderWindow& mWindow);
	~Instruction() override;

	int handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition) override;
	void draw(const Vector2f& mouse) override;
private:
	int pageIndex;
	int pageNum;
};