#pragma once
#include "SystemFunction.h"
#include "Menu.h"

enum GameMode
{
	Endless,
	Classic,
	TwoPlayer
};

enum class GameState
{
	Win,
	Lose,
	Continue,
	Pause,
	Save,
	Menu, 
	Restart
};

class System : ListTextures
{
public:
	System(View& view, RenderWindow& window);
	System(View& view, RenderWindow& window, bool check);
	bool gameLose();
	bool gameRestart();
	bool gameContinue();
	bool gameWin();
	bool gamePause();
	void setState(GameState new_state);
	void draw(const Vector2f& mouse);
	void handleEvent(const Event& event, const Vector2f& mouse);
	friend class Player;
	void				resetParameter(GameMode new_mode, int game_level = 0);
	void				writeFile(ofstream& fout);
private:
	vector<Scene*>      mainMenu;
	vector<FloatingButton>buttons;
	vector<Object>		fish_boost;
	vector<FishCoin>	fish_boost_name;
	Object      gamePaused, gameOver, gameWon;
	Object				scoreBoard;
	pair<int, int>		score;
	GameState			state;
	GameMode			game_mode;
	int					level;
	int					fish_coin;
	RenderWindow& window;
	View& view;
	InfoScore			fish_score, game_score;
private:
	void				generateNextNormalBoost(Object& curBoost);
	FishCoin			generateNextSpecialBoost(Object& curBoost);
};