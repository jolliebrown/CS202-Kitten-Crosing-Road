#include "World.h"
#include "other.h"

World::World(RenderWindow& window) :
	window(window)
{
	mapIndex.clear();
	curID = 0;
	for (int i = 0; i < 16; i++) {
		mapIndex.push_back(generateNextLaneIndex());
	}
	for (int i = 0; i < mapIndex.size(); i++)
	{
		int j = mapIndex[i];
		int pos = signMap * BaseUnit * i;
		int dir = (rand() % 2 == 0) ? -1 : 1;
		/*vector<Object> tmp;
		generate(tmp, ListTextures::background[j], j == 0 ? BaseUnit : BaseUnit * 3, pos);
		mapBackground.push(tmp);*/

		if (mapIndex[i] == 1) {
			Lane* temLane = new Road(window, dir, rand() % 3, light, animal, car, 0, pos, BaseUnit * 3, background[j], nLane);
			mLane.push_back(temLane);
		}
		else if (mapIndex[i] == 2) {
			Lane* temLane = new RailWay(window, dir, rand() % 3, tlight, train[0], 0, pos, BaseUnit * 3, background[j], nLane);
			mLane.push_back(temLane);
		}
		else if (mapIndex[i] == 0) {
			Lane* temLane = new Road(window, 100, pos, BaseUnit, obstacle[Rand(1, 100) % 2] ,background[j]);
			mLane.push_back(temLane);
		}
		else {
			if (!mLane.empty()) dir = (0 - mLane.back()->getDir());
			Lane* temLane = new Water(window, dir, wood[0], 0, pos, BaseUnit * 3, background[j], nLane);
			mLane.push_back(temLane);
		}
	}
}

World::World(RenderWindow& window, bool check) :
	window(window)
{
	mapIndex.clear();
	ifstream fin(FileName[0]);
	int map_size;
	fin >> map_size;
	for (int i = 0; i < map_size; i++)
	{
		int tmp;
		fin >> tmp;
		mapIndex.push_back(tmp);

	}
	fin.close();
	for (int i = 0; i < mapIndex.size(); i++)
	{
		int j = mapIndex[i];
		int pos = signMap * BaseUnit * i;
		int dir = (rand() % 2 == 0) ? -1 : 1;
		if (mapIndex[i] == 1) {
			Lane* temLane = new Road(window, dir, rand() % 3, light, animal, car, 0, pos, BaseUnit * 3, background[j], nLane);
			mLane.push_back(temLane);
		}
		else if (mapIndex[i] == 2) {
			Lane* temLane = new RailWay(window, dir, rand() % 3, tlight, train[0], 0, pos, BaseUnit * 3, background[j], nLane);
			mLane.push_back(temLane);
		}
		else if (mapIndex[i] == 0) {
			Lane* temLane = new Road(window, 100, pos, BaseUnit, obstacle[Rand(1, 100) % 2], background[j]);
			mLane.push_back(temLane);
		}
		else {
			if (!mLane.empty()) dir = (0 - mLane.back()->getDir());
			Lane* temLane = new Water(window, dir, wood[0], 0, pos, BaseUnit * 3, background[j], nLane);
			mLane.push_back(temLane);
		}
	}
}

World::World(RenderWindow& window, bool check, string folderName):
	window(window)
{
	mapIndex.clear();
	curID = 0;
	cerr << "Load map: \n";
	for (int i = 0; i < 16; i++) {
		string fileName = folderName + "\\" + "saveMap" + to_string(i) + ".txt";
		ifstream is(fileName);
		int mapID; 
		int pos;
		int dir;
		is >> mapID >> pos >> dir;
		cerr << "Load lane " << i << ": " << mapID << '\n';
		mapIndex.push_back(mapID);
		int j = mapIndex[i];
		if (mapIndex[i] == 1) {
			Lane* temLane = new Road(window, dir, rand() % 3, light, animal, car, 0, pos, BaseUnit * 3, background[j], nLane, is);
			mLane.push_back(temLane);
		}
		else if (mapIndex[i] == 2) {
			Lane* temLane = new RailWay(window, dir, rand() % 3, tlight, train[0], 0, pos, BaseUnit * 3, background[j], nLane, is);
			mLane.push_back(temLane);
		}
		else if (mapIndex[i] == 0) {
			Lane* temLane = new Road(window, 100, pos, BaseUnit, obstacle[Rand(1, 100) % 2], background[j], is);
			mLane.push_back(temLane);
		}
		else {
			if (!mLane.empty()) dir = (0 - mLane.back()->getDir());
			Lane* temLane = new Water(window, dir, wood[0], 0, pos, BaseUnit * 3, background[j], nLane, is);
			mLane.push_back(temLane);
		}
		is.close();
	}
	//for (int i = 0; i < mapIndex.size(); i++)
	//{
	//	int j = mapIndex[i];
	//	int pos = signMap * BaseUnit * i;
	//	int dir = (rand() % 2 == 0) ? -1 : 1;
	//	/*vector<Object> tmp;
	//	generate(tmp, ListTextures::background[j], j == 0 ? BaseUnit : BaseUnit * 3, pos);
	//	mapBackground.push(tmp);*/

	//	if (mapIndex[i] == 1) {
	//		Lane* temLane = new Road(window, dir, rand() % 3, light, animal, car, 0, pos, BaseUnit * 3, background[j], nLane);
	//		mLane.push_back(temLane);
	//	}
	//	else if (mapIndex[i] == 2) {
	//		Lane* temLane = new RailWay(window, dir, rand() % 3, tlight, train[0], 0, pos, BaseUnit * 3, background[j], nLane);
	//		mLane.push_back(temLane);
	//	}
	//	else if (mapIndex[i] == 0) {
	//		Lane* temLane = new Road(window, 100, pos, BaseUnit, obstacle[Rand(1, 100) % 2], background[j]);
	//		mLane.push_back(temLane);
	//	}
	//	else {
	//		Lane* temLane = new Water(window, dir, wood[0], 0, pos, BaseUnit * 3, background[j], nLane);
	//		mLane.push_back(temLane);
	//	}
	//}
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
			Lane* temLane = new Road(window, dir, rand() % 3, light, animal, car, 0, pos, BaseUnit * 3, background[j], nLane);
			mLane.push_back(temLane);
		}
		else if (mapIndex[i] == 2) {
			Lane* temLane = new RailWay(window, dir, rand() % 3, tlight, train[0], 0, pos, BaseUnit * 3, background[j], nLane);
			mLane.push_back(temLane);
		}
		else if (mapIndex[i] == 0) {
			Lane* temLane = new Road(window, 100, pos, BaseUnit, obstacle[Rand(1, 100) % 2], background[j]);
			mLane.push_back(temLane);
		}
		else {
			if (!mLane.empty()) dir = (0 - mLane.back()->getDir());
			Lane* temLane = new Water(window, dir, wood[0], 0, pos, BaseUnit * 3, background[j], nLane);
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

void World::draw(bool onlyLane){
	for (int i = mLane.size() - 1; i >= 0; --i) mLane[i]->draw(onlyLane);
}

void World::processEvent(System& gameSystem, Player& mPlayer)
{
	for (auto& lane : mLane) lane->handleEvent();
	//cerr << "************\n\n";
	for (auto& lane : mLane) if (lane->isCollided(mPlayer)) {
		mPlayer.setIdPlayer(-1);
		gameSystem.stopbgm();
		gameSystem.setState(GameState::Lose);
		
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
	//// cout << mLane.size() << endl;
	while (mLane.size() && curID < mLane.size()) {
		int curposition = mLane[curID]->getPosition();
		if (curposition > botView) {
			curID = 0;
			//// cout << curID << " " << curposition << " " << botView << endl;
			int nextPosition = mLane.back()->getPosition() + signMap * BaseUnit;
			mLane.erase(mLane.begin());
			//mapBackground.pop();
			mapIndex.erase(mapIndex.begin());
			int nextId = generateNextLaneIndex();
			int dir = (rand() % 2 == 0) ? -1 : 1;
			mapIndex.push_back(nextId);
			//cerr << "Add here\n\n";
			if (nextId == 1) {
				Lane* temLane = new Road(window, dir, rand() % 3, light, animal, car, 0, nextPosition, BaseUnit * 3, background[nextId], nLane);
				mLane.push_back(temLane);
			}
			else if (nextId == 2) {
				Lane* temLane = new RailWay(window, dir, rand() % 3, tlight, train[0], 0, nextPosition, BaseUnit * 3, background[nextId], nLane);
				mLane.push_back(temLane);
			}
			else if (nextId == 0) {
				Lane* temLane = new Road(window, 0, nextPosition, BaseUnit, obstacle[Rand(1, 100) % 2], background[nextId]);
				mLane.push_back(temLane);
			}
			else {
				if (!mLane.empty()) dir = (0 - mLane.back()->getDir());
				Lane* temLane = new Water(window, dir, wood[0], 0, nextPosition, BaseUnit * 3, background[nextId], nLane);
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

//int	World::getPosition(int laneIndex) {
//	return 0;
//}
//
//int World::generateNextLaneIndex(int status) {
//	static int freq[3] = { 8, 8, 2 };
//	if (status == -1) {
//		nLane = 0;
//		freq[0] = 8;
//		freq[1] = 8;
//		freq[2] = 2;
//	}
//
//	nLane += 1;
//	if (nLane % 10 == 0) {
//		if (freq[0] > 2) {
//			freq[0]--;
//			freq[1]++;
//		}
//	}
//	if (nLane < 5) {
//		return 0;
//	}
//	vector<int> randLanes;
//	for (int i = 0; i < 3; i++)
//		for (int j = 0; j < freq[i]; j++) randLanes.push_back(i);
//	int nums = Rand(0, randLanes.size() - 1);
//	return randLanes[nums];
//}

int	World::getPosition(int laneIndex) {
	return 0;
}

int World::generateNextLaneIndex(int status) {
	static int freq[4] = { 8, 8, 2, 0};
	if (status == -1) {
		nLane = 0;
		freq[0] = 8;
		freq[1] = 8;
		freq[2] = 2;
		freq[3] = 0;
	}

	nLane += 1;
	if (nLane % 10 == 0) {
		if (freq[0] > 2) {
			freq[0]--;
			freq[1]++;
			freq[3] += 2;
		}
	}
	if (nLane < 5) {
		return 0;
	}
	vector<int> randLanes;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < freq[i]; j++) randLanes.push_back(i);
	int nums = Rand(0, randLanes.size() - 1);
	return randLanes[nums];
}

bool World::isColliedObstacle(Player& mPlayer, int deltaX, int deltaY) {
	for (auto& lane : mLane) {
		for (auto obs : lane->listObstacle) {
			float curX = mPlayer.asset.getPosition().x + deltaX * BaseUnit, curY = mPlayer.asset.getPosition().y + 16.f + deltaY * BaseUnit;
			if (obs.getBound().contains(curX, curY)) {
				return true;
			}
			curX = mPlayer.asset.getPosition().x + deltaX * BaseUnit, curY = mPlayer.asset.getPosition().y + 16.f + deltaY * BaseUnit;
			if (obs.getBound().contains(curX, curY)) {
				return true;
			}
		}
	}
	return false;
}

void World::resetVehicle() {
	for (auto& lane : mLane) {
		lane->resetVehicle();
	}
}

void World::saveMap(string folderName) {
	for (int i = 0; i < mLane.size(); ++i) {
		string si = to_string(i);
		ofstream os(folderName + "\\saveMap" + si + ".txt");
		mLane[i]->saveMap(os);
	}
}