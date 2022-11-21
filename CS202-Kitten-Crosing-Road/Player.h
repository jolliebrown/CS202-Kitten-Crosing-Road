#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <map>

#include "Object.h"
#include "Command.h"
#include "Vehicle.h"

class Command;
class Player : public Object
{
public:
	int idPlayer = 0;
	void				setIdPlayer(int id);
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
	bool				movePlayer();
	bool				collision(int carX, int carY);
	//friend bool			collision(Player& mPlayer, Vehicle& mCar);
	void				changePosition(int x, int y);
	void				assignKey(Action action, sf::Keyboard::Key key);
	Keyboard::Key		getAssignedKey(Action action) const;
private:
	static bool			isRealtimeAction(Action action, Vector2i& result);
	void				test();
private:
	
	map<Keyboard::Key, Action>			mKeyBinding;
	map<Action, Vector2i>				mAction;
	// movement
	IntRect								draw_status;
	int									moveStatus = 0;
	int									isMoving = 0;
	bool								faceLeft = false;
	bool								isDead = false;
	Vector2i							moveStep;
};

// draw_status = IntRect(x, 0, 16, 16)
// Object::asset.setTextureRect(draw_status)