#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include "System.h"
#include "Object.h"
#include "World.h"
class World;
class Player : public Object
{
public:
	friend class World;
	int idPlayer = 0;
	void				setIdPlayer(int id);
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		ChangeStyle,
		ActionCount
	};
	void				draw();
						Player(RenderWindow& window, vector<Texture>& texture, int x_coor, int y_coor, int unit);
	void				handleEvent(const sf::Event& event, System& gameSystem, World &mWorld);
	void				handleRealtimeInput();
	bool				movePlayer();
	pair <float, float> getPosition() {
		return { asset.getPosition().x, asset.getPosition().y };
	}
	void				changePosition(int x, int y);
	void				setPosition(float x, float y);
	void				assignKey(Action action, sf::Keyboard::Key key);
	Keyboard::Key		getAssignedKey(Action action) const;
	void				changeAppearance(int index);
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
	Vector2i							totalMove;
	int									x, y;
	pair<int, bool>						style = {0, true};
	vector<Texture>&					texture;
};

// draw_status = IntRect(x, 0, 16, 16)
// Object::asset.setTextureRect(draw_status)