#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <map>

#include "Object.h"
#include "Command.h"

class Command;
class Player : public Object
{
public:
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		ActionCount
	};
	void				draw();
						Player(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit);
	void				handleEvent(const sf::Event& event);
	void				handleRealtimeInput();
	void				movePlayer();
	void				changePosition(int x, int y);
	void				assignKey(Action action, sf::Keyboard::Key key);
	Keyboard::Key		getAssignedKey(Action action) const;
private:
	static bool			isRealtimeAction(Action action, Vector2i& result);

private:
	map<Keyboard::Key, Action>			mKeyBinding;
	map<Action, Vector2i>				mAction;
	IntRect								draw_status;
};