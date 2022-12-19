#include "Player.h"
#include "System.h"

//void Player::draw()
//{
//		int timeMove = 100;
//		bool curMove = 0;
//		moveStatus = (moveStatus + 1) % timeMove;
//	if (isMoving > 0 && isMoving < 9)
//	{
//		curMove = moveStatus / (timeMove / 2);
//	}
//	else
//	{
//		curMove = moveStatus / (timeMove / 6);
//	}
//	draw_status = IntRect(curMove * BaseUnit, 0, BaseUnit, BaseUnit);
//	Object::asset.setTextureRect(draw_status);
//	Object::draw();
//}

void Player::draw()
{
	int curMove = 0;
	if (isDead) {
		draw_status = IntRect(8 * BaseUnit, (int)faceLeft * BaseUnit, BaseUnit, BaseUnit);
		Object::asset.setTextureRect(draw_status);
		Object::draw();
		return;
	}
	if (!isMoving)
	{
		moveStatus = (moveStatus + 1) % (TimeMove);
		curMove = moveStatus / (TimeMove / 2);
	}
	else
	{
		moveStatus = (moveStatus + 1) % (TimeMove);
		curMove = moveStatus / (TimeMove / 9);
		if (curMove < 9)
		{
			if (isMoving != curMove && curMove)
			{
			changePosition(moveStep.x, moveStep.y);
			isMoving = curMove;
			}
		}
		else
		{
			isMoving = 0;
		}
	}
	draw_status = IntRect(curMove * BaseUnit, (int) faceLeft * BaseUnit, BaseUnit, BaseUnit);
	Object::asset.setTextureRect(draw_status);
	Object::draw();
}

Player::Player(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit) : 
	Object(window, texture, x_coor, y_coor)
{
	draw_status = IntRect(0, 0, BaseUnit, BaseUnit);
	Object::asset.setTextureRect(draw_status);
	Object::unit = unit;
	mKeyBinding[Keyboard::Left] = MoveLeft;
	mKeyBinding[Keyboard::Right] = MoveRight;
	mKeyBinding[Keyboard::Up] = MoveUp;
	mKeyBinding[Keyboard::Down] = MoveDown;
}

void Player::handleEvent(const sf::Event& event, System& gameSystem)
{
	//cout << mAction.size() << endl;
	if (event.type == sf::Event::KeyReleased)
	{
	//	test();
		Vector2i tmp;
		// Check if pressed key appears in key binding, trigger command if so
		map<Keyboard::Key, Action>::iterator found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && isRealtimeAction(found->second, tmp))
		{
			map<Action, Vector2i>::iterator itr = mAction.find(found->second);
			if (itr != mAction.end())
			{
				itr->second += tmp;
			}
			else
			{
				mAction[found->second] = tmp;
			}
		}
		// no obstables
		if (mAction[Action::MoveUp].y)
		{
			if (gameSystem.score.second >= 0) 
			{
			gameSystem.score.first++;
			gameSystem.game_score.update(gameSystem.score.first, gameSystem.num_text);
			}
			else
			{
				gameSystem.score.second++;
			}
		}
		if (mAction[Action::MoveDown].y)
		{
			gameSystem.score.second--;
		}
	}
	movePlayer();
	for (int i = 0; i < 4; i++) {
		Object& boost = gameSystem.fish_boost[i];
		if (this->isCollided(boost)) {
			gameSystem.fish_coin += 1;
			gameSystem.fish_score.update(gameSystem.fish_coin, gameSystem.num_text);
			if (i != 3) gameSystem.generateNextNormalBoost(boost);
			else gameSystem.generateNextSpecialBoost(boost);
			// gen toa do moi cho no
		}
	}
}

void Player::handleRealtimeInput()
{
	//vector2i tmp;
	//map<action, vector2i>::iterator itr;
	//for (auto found : mkeybinding)
	//{
	//	// if key is pressed, lookup action and trigger corresponding command
	//	if (sf::keyboard::iskeypressed(found.first) && isrealtimeaction(found.second, tmp))
	//	{
	//		itr = maction.find(found.second);
	//		if (itr != maction.end())
	//			itr->second += tmp;
	//		else
	//			maction.insert({ found.second, tmp });
	//	}
	//}
}

bool Player::movePlayer()
{
	
	if (!mAction.empty())
	{
		moveStep = Vector2i(0, 0);
		for (auto found : mAction)
		{
			moveStep.x += found.second.x * 1.5;
			moveStep.y += found.second.y * 1.5;
		}
		if (moveStep.x < 0)
		{
			faceLeft = true;
		}
		else if (moveStep.x > 0)
		{
			faceLeft = false;
		}
		isMoving = -1;
		moveStatus = 360;
		moveStep.x /= 8;
		moveStep.y /= 8;
		mAction.clear();
		return true;
	}
	return false;
}

bool Player::isRealtimeAction(Action action, Vector2i& result)
{
	switch (action)
	{
		case MoveLeft:
			result = Vector2i(-BaseUnit, 0);
			return true;
		case MoveRight:
			result = Vector2i(BaseUnit, 0);
			return true;
		case MoveDown:
			result = Vector2i(0, BaseUnit);
			return true;
		case MoveUp:
			result = Vector2i(0, -BaseUnit);
			return true;
		default:
			return false;
	}
}

void Player::test()
{
	cerr << "my action: \n";
	for (auto itr = mAction.begin(); itr != mAction.end(); ++itr)
	{
		cerr << itr->second.x << ',' << itr->second.y << endl;
	}
}

void Player::changePosition(int x, int y)
{
	this->asset.setPosition(asset.getPosition().x + x, asset.getPosition().y + y);
}

void Player::assignKey(Action action, Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); ++itr)
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
void Player::setIdPlayer(int id) {
	idPlayer = id;
	isDead = false;
	if (idPlayer == -1) {
		mKeyBinding.clear();
		isDead = true;
	}
	else if (idPlayer == 0) {
		mKeyBinding.clear();
		mKeyBinding[Keyboard::Left] = MoveLeft;
		mKeyBinding[Keyboard::Right] = MoveRight;
		mKeyBinding[Keyboard::Up] = MoveUp;
		mKeyBinding[Keyboard::Down] = MoveDown;
	}
	else if (idPlayer == 1) {
		mKeyBinding.clear();
		mKeyBinding[Keyboard::A] = MoveLeft;
		mKeyBinding[Keyboard::D] = MoveRight;
		mKeyBinding[Keyboard::W] = MoveUp;
		mKeyBinding[Keyboard::S] = MoveDown;
	}
}