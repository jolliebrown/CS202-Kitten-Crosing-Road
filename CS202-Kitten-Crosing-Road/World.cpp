#include "World.h"
#include "other.h"

World::World(RenderWindow& window) :
	window(window)
{
	mapIndex.clear();
	curID = 0;
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
			Lane* temLane = new Road(window, dir, rand() % 3, light, car[(rand() + 1) % 3], 0, pos, BaseUnit * 3, background[j]);
			mLane.push_back(temLane);
		}
		else if (mapIndex[i] == 2) {
			Lane* temLane = new RailWay(window, dir, train[0], 0, pos, BaseUnit * 3, background[j]);
			mLane.push_back(temLane);
		}
		else {
			Lane* temLane = new Road(window, 0, pos, BaseUnit, background[j]);
			mLane.push_back(temLane);
		}
	}
}

bool World::worldRestart() {
	mapIndex.clear();
	mLane.clear();
	mapIndex.push_back(generateNextLaneIndex(-1));
	curID = 0;
	for (int i = 1; i < 16; i++) mapIndex.push_back(generateNextLaneIndex());
	for (int i = 0; i < mapIndex.size(); i++)
	{
		int j = mapIndex[i];
		int pos = signMap * BaseUnit * i;
		int dir = (rand() % 2 == 0) ? -1 : 1;
		/*vector<Object> tmp;
		generate(tmp, ListTextures::background[j], j == 0 ? BaseUnit : BaseUnit * 3, pos);
		mapBackground.push(tmp);*/

		if (mapIndex[i] == 1) {
			Lane* temLane = new Road(window, dir, rand() % 3, light, car[(rand() + 1) % 3], 0, pos, BaseUnit * 3, background[j]);
			mLane.push_back(temLane);
		}
		else if (mapIndex[i] == 2) {
			Lane* temLane = new RailWay(window, dir, train[0], 0, pos, BaseUnit * 3, background[j]);
			mLane.push_back(temLane);
		}
		else {
			Lane* temLane = new Road(window, 0, pos, BaseUnit, background[j]);
			mLane.push_back(temLane);
		}
	}
	return true;
}

World::~World()
{
	for (auto& lane : mLane) delete lane;
}

void World::writeFile(ofstream& fout)
{
	fout << mapIndex.size() << endl;
	for (int i = 0; i < mapIndex.size(); i++)
	{
		fout << mapIndex[i] << " ";
	}
	fout << endl;
}

void World::draw()
{
	for (int i = mLane.size() - 1; i >= 0; --i) mLane[i]->draw();
}

void World::processEvent(System& gameSystem, Player& mPlayer)
{
	for (auto& lane : mLane) lane->handleEvent();
	//cerr << "************\n\n";
	for (auto& lane : mLane) if (lane->isCollided(mPlayer)) {
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
		mapIndex.push_back(random);
		Object tmp(window, texture[random], i * unit, pos, unit);
		res.push_back(tmp);
	}
	// TODO: insert return statement here
	return res;
}

bool World::handleEvent(RenderWindow& window, View& mView) {
	int topView = (int)window.getView().getCenter().y;
	int botView = (int) window.getView().getCenter().y + (int) window.getView().getSize().y / 2;
	//cout << mLane.size() << endl;
	while (mLane.size() && curID < mLane.size()) {
		int curposition = mLane[curID]->getPosition();
		if (curposition > botView) {
			curID = 0;
			//cout << curID << " " << curposition << " " << botView << endl;
			int nextPosition = mLane.back()->getPosition() + signMap * BaseUnit;
			mLane.erase(mLane.begin());
			//mapBackground.pop();
			mapIndex.erase(mapIndex.begin());
			int nextId = generateNextLaneIndex();
			int dir = (rand() % 2 == 0) ? -1 : 1;
			mapIndex.push_back(nextId);
			//cerr << "Add here\n\n";
			if (nextId == 1) {
				Lane* temLane = new Road(window, dir, rand() % 3, light, car[(rand() + 1) % 3], 0, nextPosition, BaseUnit * 3, background[nextId]);
				mLane.push_back(temLane);
			}
			else if (nextId == 2) {
				Lane* temLane = new RailWay(window, dir, train[0], 0, nextPosition, BaseUnit * 3, background[nextId]);
				mLane.push_back(temLane);
			}
			else {
				Lane* temLane = new Road(window, 0, nextPosition, BaseUnit, background[nextId]);
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