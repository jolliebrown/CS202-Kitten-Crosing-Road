#pragma once
#include "SystemFunction.h"

class Scene : public ListTextures {
public:
	Scene(RenderWindow& mWindow);
	virtual ~Scene();

	virtual int			handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition) = 0;
	virtual void			draw(const Vector2f& mouse);
protected:
	RenderWindow&			window;
	vector<SystemButton>	buttons;
	vector<Object>			background;
	MenuList				sceneName;
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
	Mode(RenderWindow& mWindow);
	~Mode() override;

	int handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition) override;
	void draw(const Vector2f& mouse) override;
};

class Settings : public Scene {
public:
	Settings(RenderWindow& mWindow);
	~Settings() override;

	int handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition) override;
	void draw(const Vector2f& mouse) override;
private:

};

class Sound : public Scene {
public:
	Sound(RenderWindow& mWindow);
	~Sound() override;

	int handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition) override;
	void draw(const Vector2f& mouse) override;
private:

};

class ButtonSettings : public Scene {
public:
	ButtonSettings(RenderWindow& mWindow);
	~ButtonSettings() override;

	int handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition) override;
	void draw(const Vector2f& mouse) override;
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