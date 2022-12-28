#pragma once
#include "SystemFunction.h"

class Scene : public ListTextures {
public:
	Scene(RenderWindow& mWindow);
	virtual ~Scene();

	virtual void			handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition) = 0;
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

	void handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition) override;
	void draw(const Vector2f& mouse) override;
};

class Mode : public Scene {
public:
	Mode(RenderWindow& mWindow);
	~Mode() override;

	void handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition) override;
	void draw(const Vector2f& mouse) override;
};

class Settings : public Scene {
public:
	Settings(RenderWindow& mWindow);
	~Settings() override;

	void handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition) override;
	void draw(const Vector2f& mouse) override;
private:

};

class Sound : public Scene {
public:
	Sound(RenderWindow& mWindow);
	~Sound() override;

	void handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition) override;
	void draw(const Vector2f& mouse) override;
private:

};

class ButtonSettings : public Scene {
public:
	ButtonSettings(RenderWindow& mWindow);
	~ButtonSettings() override;

	void handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition) override;
	void draw(const Vector2f& mouse) override;
};

class Instruction : public Scene {
public:
	Instruction(RenderWindow& mWindow);
	~Instruction() override;

	void handleEvent(const Event& event, vector<Scene*>& scene, const Vector2f& mousePosition) override;
	void draw(const Vector2f& mouse) override;
private:
	int pageIndex;
	int pageNum;
};