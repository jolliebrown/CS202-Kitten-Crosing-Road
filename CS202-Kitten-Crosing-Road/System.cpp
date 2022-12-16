#include "System.h"

System::System(View& view, RenderWindow& window) :
	window(window),
	score(0),
	state(GameState::Continue),
	game_mode(GameMode::Endless),
	level(0),
	fish_coin(0),
	gamePaused(window, ListTextures::still[0], 59, 22),
	scoreBoard(window, ListTextures::still[1], 6, 5),
	view(view),
	game_score(ListTextures::numFont, window, Color(182, 137, 98, 255), 7, 28, 10),
	fish_score(ListTextures::numFont, window, Color(182, 137, 98, 255), 7, 28, 33)
{
	SystemButton pause(view, window, ListTextures::unpressed[0], ListTextures::pressed[0], 190, 6);
	pausedButtons.push_back(pause);
	for (int i = 1; i < 4; i++)
	{
		SystemButton tmp(view, window, ListTextures::unpressed[i], ListTextures::pressed[i], 101, (59 + 31 * (i - 1)));
		pausedButtons.push_back(tmp);
	}
}

System::System(View& view, RenderWindow& window, int score, GameState state, GameMode game_mode, int level, int fish_coin) :
	score(score),
	state(state),
	game_mode(game_mode),
	level(level),
	fish_coin(fish_coin),
	gamePaused(window, ListTextures::still[0], 59, 22),
	scoreBoard(window, ListTextures::still[1], 6, 5),
	window(window),
	view(view),
	game_score(ListTextures::numFont, window, Color(182, 137, 98, 255), 8, 22, 5),
	fish_score(ListTextures::numFont, window, Color(182, 137, 98, 255), 8, 22, 28)
{
	SystemButton pause(view, window, ListTextures::unpressed[0], ListTextures::pressed[0], 195, 5);
	for (int i = 1; i < 4; i++)
	{
		SystemButton tmp(view, window, ListTextures::unpressed[i], ListTextures::pressed[i], 101, 59 + 31 * (i - 1));
		pausedButtons.push_back(tmp);
	}
}

bool System::gameLose() {
	return state == Lose;
}
bool System::gameContinue() {
	return state == Continue;
}
bool System::gameWin() {
	return state == Win;
}

bool System::gamePause() {
	return state == Pause;
}
bool System::setLose() {
	//if (state != Continue && state != Lose) return false;
	state = Lose;
	return true;
}
bool System::setContinue() {
	if (state != Pause) return false;
	state = Continue;
	return true;
}
bool System::setWin() {
	//if (state != Continue && state != Win) return false;
	state = Win;
	return true;
}
bool System::setPause() {
	if (state != Continue) return false;
	state = Pause;
	return true;
}

void System::draw(const Vector2f& mouse)
{
	scoreBoard.setPos(view);
	scoreBoard.draw();
	game_score.drawWithView(view, score);
	fish_score.drawWithView(view, fish_coin);
	if (state == Continue)
	{
		pausedButtons[0].draw(mouse, false);
	}
	else if (state == Pause)
	{
		gamePaused.setPos(view);
		gamePaused.draw();
		for (int i = 1; i < pausedButtons.size(); i++)
		{
			pausedButtons[i].draw(mouse, false);
		}
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
		if (state == Continue && pausedButtons[0].isHere(mouse))
		{
			state = Pause;
		}
		else if (state == Pause)
		{
			if (pausedButtons[1].isHere(mouse))
			{
				state = Continue;
			}
		}
	}
}


SystemButton::SystemButton(View& view, RenderWindow& window, Texture& unpressed, Texture& pressed, int x_coor, int y_coor) : 
	window(window), 
	unpressed(window, unpressed, x_coor, y_coor),
	pressed(window, pressed, x_coor, y_coor + 2),
	view(view)
{
}

void SystemButton::draw(const Vector2f& mouse, const bool& isStill)
{
	unpressed.setPos(view);
	pressed.setPos(view);
	if (isStill)
		unpressed.draw();
	else
	{
		if (unpressed.isHere(mouse)) pressed.draw();
		else unpressed.draw();
	}
}

bool SystemButton::isHere(const Vector2f& mouse)
{
	return unpressed.isHere(mouse);
}
