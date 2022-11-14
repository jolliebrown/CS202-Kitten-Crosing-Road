#include "World.h"

World::World(RenderWindow& window, vector<int>& mapIndex) : window(window), mapIndex(mapIndex)
{
	for (unsigned int i = 0; i < mapIndex.size(); i++)
	{
		vector<Object> tmp;
		if (mapIndex[i] == 0) // land 
		{
			generate(tmp, ListTextures::grass, 16, 16 * i);
			grassBackground.push_back(tmp);
		}
		else if (mapIndex[i] == 1) // road
		{
			generate(tmp, ListTextures::road, 18, 16 * i - 1);
			roadBackground.push_back(tmp);
		}
		else if (mapIndex[i] == 2)
		{
			generate(tmp, ListTextures::rail, 18, 16 * i - 1);
			railBackground.push_back(tmp);
		}
	}
}

void World::draw()
{
	drawListElements(grassBackground);
	drawListElements(railBackground);
	drawListElements(roadBackground);
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