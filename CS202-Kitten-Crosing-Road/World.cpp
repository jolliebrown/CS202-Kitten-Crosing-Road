#include "World.h"

World::World(ifstream& fin, RenderWindow& window) : window(window)// chua xong
{
	int n;
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		int k;
		fin >> k;
		mapIndex.push_back(k);
	}
}

World::World(RenderWindow& window) : window(window)
{
	generate(grassBackground, ListTextures::grass, 16, 0);
	generate(roadBackground, ListTextures::road, 18, 15);
}

void World::draw()
{
	drawElement(grassBackground);
	drawElement(roadBackground);
}

vector<Object>& World::generate(vector<Object>& res, vector<Texture>& texture, int unit, int pos)
{
	res.clear();
	srand((unsigned)time(NULL));
	int countTextures = texture.size();
	cerr << countTextures;
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
