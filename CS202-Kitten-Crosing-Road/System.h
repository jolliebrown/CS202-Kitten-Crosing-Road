#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Object.h"
#include "other.h"

class InfoScore
{
private:
	Object a, b, c;
	RenderWindow& window;
	int x, y;
	int value;
public:
	InfoScore(RenderWindow& window, int x, int y, int value, vector<Texture>& texture);
	void		draw();
	void		setPos(const View& view);
	void		changePos(int _x, int _y);
	void		update(int new_value, vector<Texture>& texture);
};

class SystemButton
{
private:
	Object				unpressed;
	Object				pressed;
	RenderWindow& window;
public:
	SystemButton(View& view, RenderWindow& window, Texture& unpressed, Texture& pressed, int x_coor, int y_coor);
	SystemButton(View& view, RenderWindow& window, pair<Texture, Texture>& src, int x_coor, int y_coor);
	SystemButton(View& view, RenderWindow& window, Texture& unpressed, Texture& pressed, int x_coor, int y_coor, bool check);
	void				draw(const Vector2f& mouse, const bool& isStill);
	View&				view;
	bool				isHere(const Vector2f& mouse);
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
	System(View& view, RenderWindow& window, pair<int, int> score, GameState state, GameMode game_mode, int level, int fish_coin);
	bool gameLose();
	bool gameContinue();
	bool gameWin();
	bool gamePause();
	bool setLose();
	bool setContinue();
	bool setWin();
	bool setPause();
	void draw(const Vector2f& mouse);
	void handleEvent(const Event& event, const Vector2f& mouse);
	friend class Player;

protected:


private:
	vector<SystemButton>buttons;
	vector<Object>		fish_boost;
	Object      gamePaused, gameOver, gameWon;
	Object				scoreBoard;
	pair<int, int>		score;
	GameState			state;
	GameMode			game_mode;
	int					level;
	int					fish_coin;
	RenderWindow&		window;
	View&				view;
	InfoScore			fish_score, game_score;
	void				generateNextNormalBoost(Object& curBoost);
	void				generateNextSpecialBoost(Object& curBoost);
};

