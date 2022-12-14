#include "System.h"

System::System() :
	score(0), 
	state(GameState::Continue), 
	game_mode(GameMode::Endless), 
	level(0), 
	fish_coin(0)
{
}

System::System(int score, GameState state, GameMode game_mode, int level, int fish_coin) :
	score(score),
	state(state),
	game_mode(game_mode),
	level(level),
	fish_coin(fish_coin)
{

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