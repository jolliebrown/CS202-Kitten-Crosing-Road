#pragma once
#include <algorithm>
#include <string>

#include "SystemFunction.h"
#include "Menu.h"

const string FileName[] = { "gameData.txt", "highScore.txt", "fishboost.txt", "gameParameter.txt" };

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
	Restart,
	Setting,
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
	void drawFish();
	void draw(const Vector2f& mouse);
	void handleEvent(const Event& event, const Vector2f& mouse);
	friend class Player;
	void				resetParameter(GameMode new_mode, int game_level = 0);
	void				writeFile(ofstream& fout);
	void				writeHighScore(ofstream& fout);
	void				writeFishboost(ofstream& fout);
private:
	vector<Scene*>      mainMenu;
	vector<FloatingButton> buttons;
	vector<Object>		fish_boost;
	vector<FishCoin>	fish_boost_name;
	vector<Keyboard::Key> keyboard;
	Object				gamePaused, gameOver, gameWon;
	Object				scoreBoard;
	pair<int, int>		score;
	GameState			state;
	string				player_name = "default";
	GameMode			game_mode;
	bool				assign_key = false;
	int					level;
	int					fish_coin;
	vector<pair<int, string>> highscore;
	bool				newgame = false;
	RenderWindow&		window;
	View&				view;
	InfoScore			fish_score, game_score;
	SoundEffect			gameSE;
private:
	void				generateNextNormalBoost(Object& curBoost);
	FishCoin			generateNextSpecialBoost(Object& curBoost);
	void				updateHS();
};

bool topScore(const pair<int, string>& a, const pair<int, string>& b);