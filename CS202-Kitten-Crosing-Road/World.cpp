#include "World.h"
#include "other.h"

World::World(RenderWindow& window) :
	window(window)
{
	mapIndex = generateRangeLanes(1, 20);
	for (int i = 0; i < mapIndex.size(); i++)
	{
		int j = mapIndex[i];
		int pos = signMap * BaseUnit * i;
		int dir = (rand() % 2 == 0) ? -1 : 1;
		vector<Object> tmp;
		generate(tmp, ListTextures::background[j], j == 0 ? BaseUnit : BaseUnit * 3, pos);
		mapBackground.push(tmp);

		if (mapIndex[i] == 1) {
			Road temLane(window, dir, car[(rand() + 1) % 3], 0, pos, BaseUnit * 3);
			mLane.push_back(temLane);
		}
		else if (mapIndex[i] == 2) {
			Road temLane(window, dir, train[0], 0, pos, BaseUnit * 3, 0.5, 1);
			mLane.push_back(temLane);
		}
	}

}

void World::draw()
{
	drawListElements(mapBackground);
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
	while (!target.empty())
	{
		drawElement(target.front());
		target.pop();
	}
}