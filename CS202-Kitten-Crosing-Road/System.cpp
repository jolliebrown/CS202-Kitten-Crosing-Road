#include "System.h"

System::System(View& view, RenderWindow& window) : 
	window(window),
	score(0), 
	state(GameState::Continue), 
	game_mode(GameMode::Endless), 
	level(0), 
	fish_coin(0),
	gamePaused(window, ListTextures::still[0], 59, 22),
	view(view)
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
	window(window),
	view(view)
{
	SystemButton pause(view, window, ListTextures::unpressed[0], ListTextures::pressed[0], 195, 5);
	for (int i = 1; i < 4; i++)
	{
		SystemButton tmp(view, window, ListTextures::unpressed[i], ListTextures::pressed[i], 101, 59 + 31 * (i - 1));
		pausedButtons.push_back(tmp);
	}
}

bool System::gameLose() {
	if (state != Continue) return false;
	state = Lose;
	return true;
}
bool System::gameContinue() {
	state = Continue;
	return true;
}
bool System::gameWin() {
	if (state != Continue) return false;
	state = Win;
	return true;
}

void System::draw(const Vector2f& mouse)
{
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
