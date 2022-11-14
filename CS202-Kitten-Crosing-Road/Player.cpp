#include "Player.h"

class PlayerMover
{
public:
	PlayerMover(Vector2i move)
		: change_coor(move)
	{
	}

	void operator() (Player& mPlayer) const
	{
		mPlayer.changePosition(change_coor.x, change_coor.y);
	}

	Vector2i change_coor;
};

Player::Player(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit) : Object(window, texture, x_coor, y_coor)
{
	Object::unit = unit;
	mKeyBinding[Keyboard::Left] = MoveLeft;
	mKeyBinding[Keyboard::Right] = MoveRight;
	mKeyBinding[Keyboard::Up] = MoveUp;
	mKeyBinding[Keyboard::Down] = MoveDown;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	for (auto pair : mKeyBinding)
	{
		// If key is pressed, lookup action and trigger corresponding command
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
		case MoveLeft:
		case MoveRight:
		case MoveDown:
		case MoveUp:
			return true;
		default:
			return false;
	}
}

void Player::initializeActions()
{
	mActionBinding[MoveLeft].action = derivedAction(PlayerMover(Vector2i(-1, 0)));
	mActionBinding[MoveRight].action = derivedAction(PlayerMover(Vector2i(+1, 0)));
	mActionBinding[MoveUp].action = derivedAction(PlayerMover(Vector2i(0, -1)));
	mActionBinding[MoveDown].action = derivedAction(PlayerMover(Vector2i(0, +1)));
}

void Player::changePosition(int x, int y)
{
	asset.setPosition(asset.getPosition().x + x, asset.getPosition().y + y);
}

void Player::assignKey(Action action, Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}

Keyboard::Key Player::getAssignedKey(Action action) const
{
	for (auto pair : mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}
	return  Keyboard::Unknown;
}