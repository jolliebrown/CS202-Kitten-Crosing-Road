#include "System.h"
#include "other.h"
//System::System(View& view, RenderWindow& window) :
//	window(window),
//	score({0, 0}),
//	state(GameState::Continue),
//	game_mode(GameMode::Endless),
//	level(0),
//	fish_coin(0),
//	scoreBoard(window, ListTextures::still[1], 6, 5),
//	view(view),
//	gameOver(window, ListTextures::still[2], 59, 55),
//	gameWon(window, ListTextures::still[3], 59, 55),
//	gamePaused(window, ListTextures::still[0], 59, 22),
//	game_score(window, 28, 33, score.first, ListTextures::num_text),
//	fish_score(window, 28, 10, fish_coin, ListTextures::num_text)
//{
//	FloatingButton pause(view, window, ListTextures::systemButton[MiniButton::Pause], 195, 5);
//	buttons.push_back(pause);
//	// Pause
//	for (int i = 1; i < 4; i++)
//	{
//		FloatingButton tmp(view, window, ListTextures::systemButton[(MiniButton)i], 101, 59 + 31 * (i - 1));
//		buttons.push_back(tmp);
//	}
//	// Lose
//	for (int i = 4; i < 6; i++)
//	{
//		FloatingButton tmp(view, window, ListTextures::systemButton[(MiniButton)(8 - i)], 72 + (i - 4) * 57, 92);
//		buttons.push_back(tmp);
//	}
//	// Win
//	for (int i = 6; i < 9; i++)
//	{
//		FloatingButton tmp(view, window, ListTextures::systemButton[(MiniButton)(11 - i)], 61 + (i - 6) * 39, 92);
//		buttons.push_back(tmp);
//	}
//	for (int i = 0; i < 3; i++)
//	{
//		Object tmp(window, ListTextures::fishCoin[(FishCoin)0], 100.f, signMap * BaseUnit * i);
//		FishCoin tmp_name = FishCoin::Normal;
//		generateNextNormalBoost(tmp);
//		fish_boost.push_back(tmp);
//		fish_boost_name.push_back(tmp_name);
//	}
//	Object tmp(window, ListTextures::fishCoin[(FishCoin)3], 100.f, signMap * BaseUnit * 3);
//	FishCoin tmp_name = generateNextSpecialBoost(tmp);
//	fish_boost.push_back(tmp);
//	fish_boost_name.push_back(tmp_name);
//
//	Scene* menu_tmp = new Menu(window);
//	mainMenu.push_back(menu_tmp);
//}

System::System(View& view, RenderWindow& window, bool check) :
	window(window),
	scoreBoard(window, ListTextures::still[1], 6, 5),
	view(view),
	gameOver(window, ListTextures::still[2], 59, 55),
	gameWon(window, ListTextures::still[3], 59, 55),
	gamePaused(window, ListTextures::still[0], 59, 22),
	game_score(window, 28, 33, score.first, ListTextures::num_text),
	fish_score(window, 28, 10, fish_coin, ListTextures::num_text)
{
	ifstream fin(FileName[3]);
	ifstream fin1(FileName[1]);
	ifstream fin2(FileName[2]);
	fin >> score.first >> score.second;
	int size;
	fin1 >> size;
	for (int i = 0; i < size; i++)
	{
		pair<int, string> hs_tmp;
		fin1 >> hs_tmp.second >> hs_tmp.first;
		highscore.push_back(hs_tmp);
	}
	int state_tmp, mode_tmp;
	fin >> state_tmp >> mode_tmp;
	state = static_cast<GameState>(state_tmp);
	game_mode = static_cast<GameMode>(mode_tmp);
	fin >> level;
	fin >> fish_coin;
	cerr << "Input\n";
	FloatingButton pause(view, window, ListTextures::systemButton[MiniButton::Pause], 195, 5);
	buttons.push_back(pause);
	// Pause
	for (int i = 1; i < 4; i++)
	{
		FloatingButton tmp(view, window, ListTextures::systemButton[(MiniButton)i], 101, 59 + 31 * (i - 1));
		buttons.push_back(tmp);
	}
	// Lose
	for (int i = 4; i < 6; i++)
	{
		FloatingButton tmp(view, window, ListTextures::systemButton[(MiniButton)(8 - i)], 72 + (i - 4) * 57, 92);
		buttons.push_back(tmp);
	}
	// Win
	for (int i = 6; i < 9; i++)
	{
		FloatingButton tmp(view, window, ListTextures::systemButton[(MiniButton)(11 - i)], 61 + (i - 6) * 39, 92);
		buttons.push_back(tmp);
	}

	// no load
	for (int i = 0; i < 3; i++)
	{
		//ffish
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

	//load fish

	/*int fish_num;
	fin2 >> fish_num;
	for (int i = 0; i < fish_num; i++)
	{
		int ver_int_name;
		FishCoin tmp_name;
		fin >> ver_int_name;
		tmp_name = static_cast<FishCoin>(ver_int_name);
		fish_boost_name.push_back(tmp_name);
	}
	for (int i = 0; i < fish_num; i++)
	{
		float tmp_x, tmp_y;
		fin2 >> tmp_x >> tmp_y;
		tmp_x = view.getViewport().width / 2 - tmp_x;
		tmp_y = - view.getViewport().height / 2 - tmp_y;
		Object tmp(window, ListTextures::fishCoin[fish_boost_name[i]], tmp_x, tmp_y);
		fish_boost.push_back(tmp);
		// cout << "Done";
	}*/
	fish_score.update(fish_coin, ListTextures::num_text);
	game_score.update(score.first, ListTextures::num_text);
	Scene* menu_tmp = new Menu(window);
	mainMenu.push_back(menu_tmp);
	fin.close();
	fin2.close();
	fin1.close();

	for (int i = 0; i < 2; i++)
	{
		keyboard.push_back(Keyboard::Key::Left);
		keyboard.push_back(Keyboard::Key::Right);
		keyboard.push_back(Keyboard::Key::Up);
		keyboard.push_back(Keyboard::Key::Down);
	}
}


void System::generateNextNormalBoost(Object& curBoost) {
	Vector2f viewPosition = window.getView().getCenter();
	int curX = Rand(5, 10) * BaseUnit, curY = viewPosition.y - BaseUnit * 6.f - BaseUnit * Rand(0, 5);
	curY = curY / 16 * 16;
	curBoost.changePos((int)curX, (int)curY);
	//// cout << "done\n";
}

FishCoin System::generateNextSpecialBoost(Object& curBoost) {
	Vector2f viewPosition = window.getView().getCenter();
	int curX = Rand(5, 10) * BaseUnit, curY = viewPosition.y - BaseUnit * 6.f - BaseUnit * Rand(0, 5);
	curY = curY / 16 * 16;
	curBoost.changePos((int)curX, (int)curY);
	int rd = Rand(1, 3);
	curBoost.changeAppearance(ListTextures::fishCoin[(FishCoin)rd]);
	//// cout << "done\n";
	return (FishCoin)rd;
}

void System::writeFishboost(ofstream& fout)
{
	fout << 4 << endl;
	for (int i = 0; i < 4; i++)
	{
		fout << (int)fish_boost_name[i] << " ";
	}
	fout << endl;
	for (int i = 0; i < 4; i++)
	{
		fout << view.getCenter().x - fish_boost[i].getPos().x << " " << view.getCenter().y - fish_boost[i].getPos().y;
		fout << endl;
	}
}

bool topScore(const pair<int, string>& a, const pair<int, string>& b)
{
	return a.first > b.first || (a.first == b.first && a.second > b.second);
}

void System::updateHS()
{
	pair<int, string> tmp = { score.first, player_name };
	highscore.push_back(tmp);
	sort(highscore.begin(), highscore.end(), topScore);
	for (int i = 0; i < highscore.size(); i++)
	{
		cerr << highscore[i].first << " ";
	}
	cerr << endl;
}

void System::writeFile(ofstream& fout)
{
	fout << score.first << " " << score.second << endl;
	fout << (int)state << endl;
	fout << (int)game_mode << endl;
	fout << level << endl;
	fout << fish_coin << endl;
}

// 10
void System::writeHighScore(ofstream& fout)
{
	int size = highscore.size();
	size = size < 10 ? size : 10;
	fout << size << endl;
	for (int i = 0; i < size ; i++)
	{
		fout << highscore[i].second << endl;
		fout << highscore[i].first << endl;
	}
}

void System::resetParameter(GameMode new_mode, int game_level)
{
	score = { 0, 0 };
	game_mode = new_mode;
	level = game_level;
}

bool System::gameRestart() {
	return state == GameState::Restart;
}
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

void System::setState(GameState new_state)
{
	state = new_state;
	if (new_state == GameState::Lose)
	{
		gameSE.playEffect(SFX::Lose);
		updateHS();
	}
}

void System::drawFish() {
	for (int i = 0; i < fish_boost.size(); i++)
	{
		fish_boost[i].draw();
	}
}

void System::draw(const Vector2f& mouse)
{
	if (state == GameState::Pause)
	{
		// cout << "Paused\n";
	}
	//state = GameState::Menu;
	scoreBoard.setPos(view);
	scoreBoard.draw();
	game_score.draw();
	fish_score.draw();
	int l = 0, r = 0;
	if (state == GameState::Menu || state == GameState::Setting)
	{
		view.reset(FloatRect(0, 0, BaseUnit * 14, BaseUnit * 10));
		mainMenu.back()->draw(mouse);
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
	if (event.type == Event::MouseButtonReleased || event.type == Event::KeyReleased)
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
			else if (buttons[2].isHere(mouse))
			{
				state = GameState::Setting;
				Scene* settingScene = new ButtonSettings(window);
				mainMenu.push_back(settingScene);
			}
			else if (buttons[3].isHere(mouse))
			{
				state = GameState::Menu;
			}
		}
		else if (state == GameState::Setting)
		{
			int tmp_menu = mainMenu.back()->handleEvent(event, mainMenu, mouse);
			if (tmp_menu == -100)
			{
				state = GameState::Continue;
			}
			else if (tmp_menu > 9)
			{
				assign_key = true;
				vector<Keyboard::Key> key_tmp = mainMenu.back()->getKeyboard();
				for (int i = 0; i < 4; i++)
				{
					keyboard[i] = keyboard[i + 4];
					keyboard[i + 4] = key_tmp[i];
				}
			}
		}
		else if (state == GameState::Menu)
		{
			int tmp_menu = mainMenu.back()->handleEvent(event, mainMenu, mouse);
			if (tmp_menu == 2)
			{
				gameSE.playEffect(SFX::Intro);
				if (newgame)
				{
					state = GameState::Restart;
					resetParameter(GameMode::Endless);
					game_score.update(score.first, ListTextures::num_text);
					newgame = false;
				}
				else
				{
					state = GameState::Continue;
				}
			}
			else if (tmp_menu == 1)
			{
				// classic mode
			}
			else if (tmp_menu == -2)
			{
				//gameSE.playEffect(SFX::Intro);
				newgame = true;
			}
			else if (tmp_menu > 9)
			{
				assign_key = true;
				vector<Keyboard::Key> key_tmp = mainMenu.back()->getKeyboard();
				for (int i = 0; i < 4; i++)
				{
					keyboard[i] = keyboard[i + 4];
					keyboard[i + 4] = key_tmp[i];
				}
			}
		}
		else if (state == GameState::Lose)
		{
			if (buttons[4].isHere(mouse))
			{
				gameSE.playEffect(SFX::Intro);
				state = GameState::Restart;
				resetParameter(game_mode);
				game_score.update(score.first, ListTextures::num_text);
			}
			else if (buttons[5].isHere(mouse))
			{
				state = GameState::Menu;
			}
		}
	}
	if (state != GameState::Menu)
	{
		gameSE.bgm.stop();
	}
	else if (state == GameState::Menu && gameSE.bgm.getStatus() == SoundSource::Stopped)
	{
		gameSE.bgm.play();
	}
	if (state == GameState::Continue && gameSE.road_bgm.getStatus() != SoundSource::Playing)
	{
		gameSE.road_bgm.play();
	}
	else if (state != GameState::Continue)
	{
		gameSE.road_bgm.pause();
	}
}


