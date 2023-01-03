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
				// new solution
				moveStep.x = totalMove.x / (9 - curMove);
				moveStep.y = totalMove.y / (9 - curMove);
				totalMove.x -= moveStep.x;
				totalMove.y -= moveStep.y;
			changePosition(moveStep.x, moveStep.y);
			isMoving = curMove;
			}
		}
		else
		{
			/*cout << "jump\n";
			int new_x = (getPosition().first - x);
			new_x /= BaseUnit;
			new_x = new_x * BaseUnit + x;
			int new_y = (getPosition().second - y);
			new_y /= BaseUnit;
			new_y = new_y * BaseUnit + y;
			this->asset.setPosition(new_x, new_y);*/
			isMoving = 0;
			cout << int(getPosition().first) % BaseUnit  << " " << int(getPosition().second) % BaseUnit << endl;
		}
	}
	draw_status = IntRect(curMove * BaseUnit, (int) faceLeft * BaseUnit, BaseUnit, BaseUnit);
	Object::asset.setTextureRect(draw_status);
	Object::draw();
}

Player::Player(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit) : 
	Object(window, texture, x_coor, y_coor), x(x_coor), y(y_coor)
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
		gameSystem.gameSE.playEffect(SFX::Move);
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
		/*if (mAction[Action::MoveUp].y)
		{
			if (gameSystem.score.second >= 0)
			{
				gameSystem.score.first++;
				cout << "1\n";
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
		}*/
		if (mAction[Action::MoveUp].y)
		{
			int pos_y = getPosition().second;
			if (abs(pos_y - gameSystem.score.second) > 15)
			{
				gameSystem.score.first++;
				gameSystem.score.second = pos_y;
				cout << "1\n";
				gameSystem.game_score.update(gameSystem.score.first, gameSystem.num_text);
			}
		}
	}
	movePlayer();
	for (int i = 0; i < 4; i++) {
		Object& boost = gameSystem.fish_boost[i];
		if (this->isCollidedSpecial(boost)) {
			gameSystem.gameSE.playEffect(SFX::Coin);
			if (i != 3)
			{
				gameSystem.fish_coin += 1;
				gameSystem.generateNextNormalBoost(boost);
			}
			else
			{
				FishCoin& tmp = gameSystem.fish_boost_name[3];
				if (tmp == FishCoin::Bonus)
				{
					gameSystem.fish_coin += 5;
					cout << 5 << endl;
				}
				else
				{
					gameSystem.fish_coin += 1;
				}
				gameSystem.generateNextSpecialBoost(boost);
			}
			gameSystem.fish_score.update(gameSystem.fish_coin, gameSystem.num_text);
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
		for (auto found : mAction)
		{
			totalMove.x += found.second.x * 1.0;
			totalMove.y += found.second.y * 1.0;
		}
		if (totalMove.x < 0)
		{
			faceLeft = true;
		}
		else if (totalMove.x > 0)
		{
			faceLeft = false;
		}
		/*isMoving = -1;
		moveStatus = 360;
		moveStep.x /= 8;
		moveStep.y /= 8;*/

		// alternative solution
		/*if (!moveStep.y)
		{
			isMoving = -1;
			moveStatus = 360;
			moveStep.x /= 8;
			moveStep.y /= 8;
		}
		else
		{
			changePosition(0, moveStep.y / 2);
			moveStep.y = 0;
			isMoving = -1;
			moveStatus = 360;
			moveStep.x /= 8;
		}*/

		// new solution
		if (!isMoving)
			isMoving = -1;
		moveStatus = 360;
		mAction.clear();
		return true;
	}
	return false;
}

//bool Player::movePlayer()
//{
//	map<Action, Vector2i>::iterator left = mAction.find(Action::MoveLeft);
//	map<Action, Vector2i>::iterator right = mAction.find(Action::MoveRight);
//	if (!mAction.empty())
//	{
//		if (left != mAction.end() || right != mAction.end())
//		{
//			moveStep = Vector2i(0, 0);
//			if (left != mAction.end())
//			{
//				moveStep.x += left->second.x * 1.0;
//				moveStep.y += left->second.y * 1.0;
//			}
//			if (right != mAction.end())
//			{
//				moveStep.x += right->second.x * 1.0;
//				moveStep.y += right->second.y * 1.0;
//			}
//			if (moveStep.x < 0)
//			{
//				faceLeft = true;
//			}
//			else if (moveStep.x > 0)
//			{
//				faceLeft = false;
//			}
//			isMoving = -1;
//			moveStatus = 360;
//			moveStep.x /= 8;
//			moveStep.y /= 8;
//			mAction.clear();
//			return true;
//		}
//	}
//	return false;
//}

bool Player::isRealtimeAction(Action action, Vector2i& result)
{
	switch (action)
	{
		case MoveLeft:
			result = Vector2i(-BaseUnit /2, 0);
			return true;
		case MoveRight:
			result = Vector2i(BaseUnit / 2, 0);
			return true;
		case MoveDown:
			result = Vector2i(0, BaseUnit /2);
			return true;
		case MoveUp:
			result = Vector2i(0, -BaseUnit /2);
			return true;
		default:
			return false;
	}
}

void Player::test()
{
	//cerr << "my action: \n";
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