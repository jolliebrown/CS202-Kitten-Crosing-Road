#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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
						Player(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit);
	void				handleEvent(const sf::Event& event, CommandQueue& commands);
	void				handleRealtimeInput(CommandQueue& commands);

	void				changePosition(int x, int y);
	void				assignKey(Action action, sf::Keyboard::Key key);
	Keyboard::Key		getAssignedKey(Action action) const;
private:
	void				initializeActions();
	static bool			isRealtimeAction(Action action);

private:
	std::map<Keyboard::Key, Action>		mKeyBinding;
	std::map<Action, Command>			mActionBinding;
	IntRect								draw_status;
};