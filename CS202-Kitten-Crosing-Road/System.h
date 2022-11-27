#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>

class System
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
	System();
	System(int score, GameState state, GameMode game_mode, int level, int fish_coin);
private:
	int					score;
	GameState			state;
	GameMode			game_mode;
	int					level;
	int					fish_coin;
};