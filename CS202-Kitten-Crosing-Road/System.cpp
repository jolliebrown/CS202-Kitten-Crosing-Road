#include "System.h"

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
	//game_score(ListTextures::numFont, window, Color(182, 137, 98, 255), 7, 28, 10),
	//fish_score(ListTextures::numFont, window, Color(182, 137, 98, 255), 7, 28, 33)
	gamePaused(window, ListTextures::still[0], 59, 22),
	game_score(window, 28, 33, score.first, ListTextures::num_text),
	fish_score(window, 28, 10, fish_coin, ListTextures::num_text)
{
	SystemButton pause(view, window, ListTextures::systemButton[MiniButton::Pause], 195, 5);
	buttons.push_back(pause);
	for (int i = 1; i < 4; i++)
	{
		SystemButton tmp(view, window, ListTextures::systemButton[(MiniButton)i], 101, 59 + 31 * (i - 1));
		buttons.push_back(tmp);
	}
	for (int i = 4; i < 6; i++)
	{
		SystemButton tmp(view, window, ListTextures::systemButton[(MiniButton)(8 - i)], 72 + (i - 4) * 57, 92);
		buttons.push_back(tmp);
	}
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
	game_score.draw();
	fish_score.draw();
	if (state == GameState::Continue)
	{
		buttons[0].draw(mouse, false);
	}
	else if (state == GameState::Pause)
	{
		gamePaused.setPos(view);
		gamePaused.draw();
		for (int i = 1; i < 4; i++)
		{
			buttons[i].draw(mouse, false);
		}
	}
	else if (state == GameState::Lose)
	{
		gameOver.setPos(view);
		gameOver.draw();
		for (int i = 4; i < 6; i++)
		{
			buttons[i].draw(mouse, false);
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
		if (state == Continue && buttons[0].isHere(mouse))
		{
			state = Pause;
		}
		else if (state == Pause)
		{
			if (buttons[1].isHere(mouse))
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

SystemButton::SystemButton(View& view, RenderWindow& window, pair<Texture, Texture>& src, int x_coor, int y_coor) :
	window(window),
	unpressed(window, src.first, x_coor, y_coor),
	pressed(window, src.second, x_coor, y_coor + 2),
	view(view)
{
}

SystemButton::SystemButton(View& view, RenderWindow& window, Texture& unpressed, Texture& pressed, int x_coor, int y_coor, bool check) :
	window(window),
	unpressed(window, unpressed, x_coor, y_coor),
	pressed(window, pressed, x_coor, y_coor),
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
InfoScore::InfoScore(RenderWindow& window, int x, int y, int value, vector<Texture>& texture) :
	window(window),
	x(x), y(y), value(value), 
	a(window, texture[0], x, y),
	b(window, texture[0], x + 6, y),
	c(window, texture[0], x + 12, y)
{
	update(value, texture);
}

void InfoScore::draw()
{
	setPos(window.getView());
	a.draw();
	b.draw();
	c.draw();
}

void InfoScore::setPos(const View& view)
{
	a.setPos(view);
	b.setPos(view);
	c.setPos(view);
}

void InfoScore::changePos(int _x, int _y)
{
	a.changePos(_x, _y);
	b.changePos(_x + 7, _y);
	c.changePos(_x + 14, _y);
}

void InfoScore::update(int new_value, vector<Texture>& texture)
{
	int a_text = new_value / 100 % 10;
	int b_text = new_value / 10 % 10;
	int c_text = new_value % 10;

	a.setTexture(texture[a_text]);
	b.setTexture(texture[b_text]);
	c.setTexture(texture[c_text]);
}
