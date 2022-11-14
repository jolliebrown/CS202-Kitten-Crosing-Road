#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <functional>
#include <cassert>
#include <queue>
#include <utility>

namespace Category
{
	enum Type
	{
		None = 0,
		Background = 1 << 0,
		Projectile = 1 << 1,
		Player = 1 << 2,
		Pickup = 1 << 3,
	};
}

typedef std::function<void(Vector2i& move)> Action;

class Command
{
public:
	Command();

	Action						action;
	unsigned int				category;
};

class CommandQueue
{
public:
	void						push(const Command& command);
	Command						pop();
	bool						isEmpty() const;


private:
	std::queue<Command>			mQueue;
};

template <typename Function>
Action derivedAction(Function fn)
{
	return [=](Vector2i& move)
	{
		// Check if cast is safe
		//assert(dynamic_cast<GameObject*>(move) != nullptr);

		// Downcast node and invoke function on it
		fn(move);
	};
}