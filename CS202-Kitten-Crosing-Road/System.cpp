#include "System.h"
#include "other.h"
System::System(View& view, RenderWindow& window) :
	window(window),
	score({0, 0}),
	state(GameState::Continue),
	game_mode(GameMode::Endless),
	level(0),
	fish_coin(0),
	scoreBoard(window, ListTextures::still[1], 6, 5),
	view(view),
	gameOver(window, ListTextures::still[2], 59, 55),
	gameWon(window, ListTextures::still[3], 59, 55),
	gamePaused(window, ListTextures::still[0], 59, 22),
	game_score(window, 28, 33, score.first, ListTextures::num_text),
	fish_score(window, 28, 10, fish_coin, ListTextures::num_text)
{
	FloatingButton pause(view, window, ListTextures::systemButton[MiniButton::Pause], 195, 5);
	buttons.push_back(pause);
	for (int i = 1; i < 4; i++)
	{
		FloatingButton tmp(view, window, ListTextures::systemButton[(MiniButton)i], 101, 59 + 31 * (i - 1));
		buttons.push_back(tmp);
	}
	for (int i = 4; i < 6; i++)
	{
		FloatingButton tmp(view, window, ListTextures::systemButton[(MiniButton)(8 - i)], 72 + (i - 4) * 57, 92);
		buttons.push_back(tmp);
	}
	for (int i = 6; i < 9; i++)
	{
		FloatingButton tmp(view, window, ListTextures::systemButton[(MiniButton)(11 - i)], 61 + (i - 6) * 39, 92);
		buttons.push_back(tmp);
	}
	for (int i = 0; i < 3; i++)
	{
		Object tmp(window, ListTextures::fishCoin[(FishCoin)0], 100.f, signMap * BaseUnit * i);
		FishCoin tmp_name = FishCoin::Normal;
		generateNextNormalBoost(tmp);
		fish_boost.push_back(tmp);
		fish_boost_name.push_back(tmp_name);
	}
	Object tmp(window, ListTextures::fishCoin[(FishCoin)3], 100.f, signMap * BaseUnit * 3);
	FishCoin tmp_name = generateNextSpecialBoost(tmp);
	fish_boost.push_back(tmp);
	fish_boost_name.push_back(tmp_name);

	Scene* menu_tmp = new Menu(window);
	mainMenu.push_back(menu_tmp);
}


void System::generateNextNormalBoost(Object& curBoost) {
	Vector2f viewPosition = window.getView().getCenter();
	int curX = Rand(5, 10) * BaseUnit, curY = viewPosition.y - BaseUnit * 6.f - BaseUnit * Rand(0, 5);
	curY = curY / 16 * 16;
	curBoost.changePos((int)curX, (int)curY);
}

FishCoin System::generateNextSpecialBoost(Object& curBoost) {
	Vector2f viewPosition = window.getView().getCenter();
	int curX = Rand(5, 10) * BaseUnit, curY = viewPosition.y - BaseUnit * 6.f - BaseUnit * Rand(0, 5);
	curY = curY / 16 * 16;
	curBoost.changePos((int)curX, (int)curY);
	int rd = Rand(1, 3);
	curBoost.changeAppearance(ListTextures::fishCoin[(FishCoin)rd]);
	return (FishCoin)rd;
}

//System::System(View& view, RenderWindow& window, pair<int, int> score, GameState state, GameMode game_mode, int level, int fish_coin) :
//	score(score),
//	state(state),
//	game_mode(game_mode),
//	level(level),
//	fish_coin(fish_coin),
//	gamePaused(window, ListTextures::still[0], 59, 22),
//	gameOver(window, ListTextures::still[2], 59, 55),
//	scoreBoard(window, ListTextures::still[1], 6, 5),
//	window(window),
//	view(view),
//	//fish_score(ListTextures::numFont, window, Color(182, 137, 98, 255), 8, 22, 28)
//	game_score(window, 28, 33, score.first, ListTextures::num_text),
//	fish_score(window, 28, 10, fish_coin, ListTextures::num_text)
//{
//	SystemButton pause(view, window, ListTextures::systemButton[MiniButton::Pause], 195, 5);
//	for (int i = 1; i < 4; i++)
//	{
//		SystemButton tmp(view, window, ListTextures::systemButton[(MiniButton)i], 101, 59 + 31 * (i - 1));
//		buttons.push_back(tmp);
//	}
//	for (int i = 4; i < 6; i++)
//	{
//		SystemButton tmp(view, window, ListTextures::systemButton[(MiniButton)(8 - i)], 72 + (i - 4) * 57, 92);
//		buttons.push_back(tmp);
//	}
//}

bool System::gameLose() {
	return state == GameState::Lose;
}
bool System::gameContinue() {
	return state == GameState::Continue;
}
bool System::gameWin() {
	return state == GameState::Win;
}

bool System::gamePause() {
	return state == GameState::Pause;
}
bool System::setLose() {
	//if (state != Continue && state != Lose) return false;
	state = GameState::Lose;
	return true;
}
bool System::setContinue() {
	if (state != GameState::Pause) return false;
	state = GameState::Continue;
	return true;
}
bool System::setWin() {
	//if (state != Continue && state != Win) return false;
	state = GameState::Win;
	return true;
}
bool System::setPause() {
	if (state != GameState::Continue) return false;
	state = GameState::Pause;
	return true;
}

void System::draw(const Vector2f& mouse)
{
	//state = GameState::Menu;
	for (int i = 0; i < fish_boost.size(); i++)
	{
		fish_boost[i].draw();
	}
	scoreBoard.setPos(view);
	scoreBoard.draw();
	game_score.draw();
	fish_score.draw();
	int l = 0, r = 0;
	if (state == GameState::Menu)
	{
		view.reset(FloatRect(0, 0, BaseUnit * 14, BaseUnit * 10));
		mainMenu[0]->draw(mouse);
	}
	else if (state == GameState::Continue)
	{
		buttons[0].draw(mouse, false);
	}
	else if (state == GameState::Pause)
	{
		gamePaused.setPos(view);
		gamePaused.draw();
		buttons[0].draw(mouse, true);
		l = 1;
		r = 4;
	}
	else if (state == GameState::Lose)
	{
		gameOver.setPos(view);
		gameOver.draw();
		l = 4;
		r = 6;
	}
	else if (state == GameState::Win)
	{
		gameWon.setPos(view);
		gameWon.draw();
		l = 6;
		r = 9;
	}
	for (int i = l; i < r; i++)
	{
		buttons[i].draw(mouse, false);
	}
}

string convertScore(int a)
{
	if (a < 0) return "";
	if (a == 0) return "000";
	if (a < 10) return "00" + to_string(a);
	if (a < 100) return "0" + to_string(a);
	return to_string(a);
}

void System::handleEvent(const Event& event, const Vector2f& mouse)
{
	if (event.type == Event::MouseButtonReleased)
	{
		if (state == GameState::Continue && buttons[0].isHere(mouse))
		{
			state = GameState::Pause;
		}
		else if (state == GameState::Pause)
		{
			if (buttons[1].isHere(mouse))
			{
				state = GameState::Continue;
			}
		}
	}
}



