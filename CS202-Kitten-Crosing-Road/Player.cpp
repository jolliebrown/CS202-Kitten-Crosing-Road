#include "Player.h"

void Player::draw()
{
	Object::draw();
	movePlayer();
}

Player::Player(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit) : Object(window, texture, x_coor, y_coor)
{
	draw_status = IntRect(0, 0, 16, 16);
	Object::asset.setTextureRect(draw_status);
	Object::unit = unit;
	mKeyBinding[Keyboard::Left] = MoveLeft;
	mKeyBinding[Keyboard::Right] = MoveRight;
	mKeyBinding[Keyboard::Up] = MoveUp;
	mKeyBinding[Keyboard::Down] = MoveDown;
}

void Player::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		Vector2i tmp;
		// Check if pressed key appears in key binding, trigger command if so
		map<Keyboard::Key, Action>::iterator found = mKeyBinding.find(event.key.code);
		cout << event.key.code;
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second, tmp))
		{
			cerr << "im here";
			map<Action, Vector2i>::iterator itr = mAction.find(found->second);
			if (itr != mAction.end())
			{
				itr->second += tmp;
				cerr << "ok";
			}
			else
			{
				mAction[found->second] = tmp;
				cerr << "ok no";
			}
		}
	}
}

void Player::handleRealtimeInput()
{
	Vector2i tmp;
	map<Action, Vector2i>::iterator itr;
	for (auto found : mKeyBinding)
	{
		// If key is pressed, lookup action and trigger corresponding command
		if (sf::Keyboard::isKeyPressed(found.first) && isRealtimeAction(found.second, tmp))
		{
			itr = mAction.find(found.second);
			if (itr != mAction.end())
				itr->second += tmp;
			else
				mAction.insert({ found.second, tmp });
		}
	}
}

void Player::movePlayer()
{
	for (auto found : mAction)
	{
		cout << found.second.x << " "<< found.second.y << endl;
	}
}

bool Player::isRealtimeAction(Action action, Vector2i& result)
{
	switch (action)
	{
		case MoveLeft:
			result = Vector2i(-1, 0);
			return true;
		case MoveRight:
			result = Vector2i(1, 0);
			return true;
		case MoveDown:
			result = Vector2i(0, 1);
			return true;
		case MoveUp:
			result = Vector2i(0, -1);
			return true;
		default:
			return false;
	}
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