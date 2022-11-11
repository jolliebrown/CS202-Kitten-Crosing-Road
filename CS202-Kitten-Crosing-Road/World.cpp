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

}
