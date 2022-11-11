#include "Object.h"

ListTextures::ListTextures()
{
	// load het asset vao day nha
}

Object::Object(RenderWindow& window, Texture& texture, int x_coor, int y_coor) : window(window), mAsset(texture)
{
	asset.setPosition((float)x_coor, (float)y_coor);
	bound = asset.getGlobalBounds();
}

void Object::draw()
{
	window.draw(asset);
}

vector<Texture>& ListTextures::load(string fileName, int x_coor, int y_coor, int width, int height, int unit)
{
	vector<Texture> res;
	for (int i = x_coor; (i - x_coor) * unit < width; i++)
	{
		for (int j = y_coor; (j - y_coor) * unit < height; j++)
		{
			Texture tmp;
			tmp.loadFromFile(fileName, IntRect(i, j, unit, unit));
			res.push_back(tmp);
		}
	}
	// TODO: insert return statement here
	return res;
}
