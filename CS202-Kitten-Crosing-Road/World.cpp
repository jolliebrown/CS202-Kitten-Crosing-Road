#include "World.h"

World::World(RenderWindow& window, vector<int>& mapIndex) :
	window(window), 
	mapIndex(mapIndex)
{
	for (int i = 0; i < mapIndex.size(); i++)
	{
		int j = mapIndex[i];
		vector<Object> tmp;
		generate(tmp, ListTextures::background[j], j == 0 ? BaseUnit : BaseUnit * 3, signMap * BaseUnit * i);
		mapBackground.push(tmp);
	}
}

void World::draw()
{
	drawListElements(mapBackground);
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