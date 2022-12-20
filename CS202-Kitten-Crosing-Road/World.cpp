#include "World.h"
#include "other.h"

World::World(RenderWindow& window) :
	window(window)
{
	mapIndex.clear();
	for (int i = 0; i < 16; i++) mapIndex.push_back(generateNextLaneIndex());
	for (int i = 0; i < mapIndex.size(); i++)
	{
		int j = mapIndex[i];
		int pos = signMap * BaseUnit * i;
		int dir = (rand() % 2 == 0) ? -1 : 1;
		/*vector<Object> tmp;
		generate(tmp, ListTextures::background[j], j == 0 ? BaseUnit : BaseUnit * 3, pos);
		mapBackground.push(tmp);*/

		if (mapIndex[i] == 1) {
			Road temLane(window, dir, car[(rand() + 1) % 3], 0, pos, BaseUnit * 3, background[j]);
			mLane.push_back(temLane);
		}
		else if (mapIndex[i] == 2) {
			Road temLane(window, dir, train[0], 0, pos, BaseUnit * 3, 0.5, 1, background[j]);
			mLane.push_back(temLane);
		}
		else {
			Road temLane(window, 0, pos, BaseUnit, background[j]);
			mLane.push_back(temLane);
		}
	}
}

void World::draw()
{
	//drawListElements(mapBackground);
	for (auto& lane : mLane) lane.draw();
}

void World::processEvent(System& gameSystem, Player& mPlayer)
{
	for (auto& lane : mLane) lane.handleEvent();
	for (auto& lane : mLane) if (lane.isCollided(mPlayer)) {
		mPlayer.setIdPlayer(-1);
		gameSystem.setLose();
		break;
	}
}

vector<Object>& World::generate(vector<Object>& res, vector<Texture>& texture, int unit, int pos)
{
	res.clear();
	int countTextures = texture.size();
	for (int i = 0; i < range; i++)
	{
		int random = rand()% countTextures;
		Object tmp(window, texture[random], i * unit, pos, unit);
		res.push_back(tmp);
	}
	// TODO: insert return statement here
	return res;
}

void World::drawElement(vector<Object>& target)
{
	for (unsigned int i = 0; i < target.size(); i++)
	{
		target[i].draw();
	}
}

void World::drawListElements(vector<vector<Object>>& target)
{
	for (unsigned int i = 0; i < target.size(); i++)
	{
		drawElement(target[i]);
	}
}

void World::drawListElements(queue<vector<Object>> target)
{
	return;
	while (!target.empty())
	{
		drawElement(target.front());
		target.pop();
	}
}

bool World::handleEvent(RenderWindow& window, View& mView) {
	int topView = (int)window.getView().getCenter().y;
	int botView = (int) window.getView().getCenter().y + (int) window.getView().getSize().y / 2;
	cout << mLane.size() << endl;
	while (mLane.size()) {
		int curposition = mLane[0].getPosition();
		if (curposition > botView) {
			int nextPosition = mLane.back().getPosition() + signMap * BaseUnit;
			mLane.erase(mLane.begin());
			//mapBackground.pop();
			mapIndex.erase(mapIndex.begin());
			int nextId = generateNextLaneIndex();
			int dir = (rand() % 2 == 0) ? -1 : 1;
			mapIndex.push_back(nextId);
			if (nextId == 1) {
				Road temLane(window, dir, car[(rand() + 1) % 3], 0, nextPosition, BaseUnit * 3, background[nextId]);
				mLane.push_back(temLane);
			}
			else if (nextId == 2) {
				Road temLane(window, dir, train[0], 0, nextPosition, BaseUnit * 3, 0.5, 1, background[nextId]);
				mLane.push_back(temLane);
			}
			else {
				Road temLane(window, 0, nextPosition, BaseUnit, background[nextId]);
				mLane.push_back(temLane);
			}
			/*vector<Object> tmp;
			generate(tmp, ListTextures::background[nextId], nextId == 0 ? BaseUnit : BaseUnit * 3, nextPosition);
			mapBackground.push(tmp);*/
		}
		else return true;
		
	}
	return false;
}

int	World::getPosition(int laneIndex) {
	return 0;
}