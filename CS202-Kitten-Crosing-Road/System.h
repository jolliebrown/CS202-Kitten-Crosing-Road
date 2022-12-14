#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Object.h"

class SystemButton
{
public:
	Object				unpressed;
	Object				pressed;
	RenderWindow& window;
public:
	SystemButton(View& view, RenderWindow& window, Texture& unpressed, Texture& pressed, int x_coor, int y_coor);
	void				draw(const Vector2f& mouse, const bool& isStill);
	View&				view;
};

class System : ListTextures
{
public:
	enum GameState
	{
		Win,
		Lose,
		Continue,
		Pause,
		Save
	};
	enum GameMode
	{
		Endless,
		Classic,
		TwoPlayer
	};
	System(View& view, RenderWindow& window);
	System(View& view, RenderWindow& window, int score, GameState state, GameMode game_mode, int level, int fish_coin);
	bool gameLose();
	bool gameContinue();
	bool gameWin();
	void draw(const Vector2f& mouse);
private:
	vector<SystemButton>pausedButtons;
	Object				gamePaused;
	int					score;
	GameState			state;
	GameMode			game_mode;
	int					level;
	int					fish_coin;
	RenderWindow&		window;
	View&				view;
};

