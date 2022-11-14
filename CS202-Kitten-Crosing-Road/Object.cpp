#include "Object.h"

ListTextures::ListTextures()
{
	// load het asset vao day nha
	load(grass, "Media/Grass.png", 0, 0, 48, 32, 16);
	load(road, "Media/Road.png", 0, 0, 48, 18, 18);
	load(rail, "Media/Rail.png", 0, 0, 48, 18, 18);

	onePicLoad(user, "Media/Binh.png", 0, 0, 112, 16);
}

Object::Object(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit) : window(window), mAsset(texture), unit(unit)
{
	asset.setTexture(mAsset);
	asset.setPosition((float)x_coor, (float)y_coor);
	bound = asset.getGlobalBounds();
}

Object::Object(RenderWindow& window, Texture& texture, int x_coor, int y_coor) : window(window), mAsset(texture), unit(unit)
{
	unit = 0;
	asset.setTexture(mAsset);
	asset.setPosition((float)x_coor, (float)y_coor);
	bound = asset.getGlobalBounds();
}

Object::Object(const Object& scr) : window(scr.window), unit(scr.unit), mAsset(scr.mAsset)
{
	asset.setTexture(mAsset);
	float x_coor = scr.asset.getPosition().x;
	float y_coor = scr.asset.getPosition().y;
	asset.setPosition(x_coor, y_coor);
	bound = asset.getGlobalBounds();
}

//Object& Object::operator=(const Object& scr)
//{
//	this->unit = scr.unit;
//	this->mAsset = scr.mAsset;
//
//	// TODO: insert return statement here
//}

void Object::draw()
{
	window.draw(asset);
}

vector<Texture>& ListTextures::load(vector<Texture>& scr, string fileName, int x_coor, int y_coor, int width, int height, int unit)
{
	scr.clear();
	for (int i = 0; (i * unit + x_coor)  < width; i++)
	{
		for (int j = 0; (j * unit + y_coor)  < height; j++)
		{
			Texture tmp;
			tmp.loadFromFile(fileName, IntRect(i * unit + x_coor, j * unit + y_coor, unit, unit));
			scr.push_back(tmp);
		} 
	}
	// TODO: insert return statement here
	return scr;
}

vector<Texture>& ListTextures::onePicLoad(vector<Texture>& scr, string fileName, int x_coor, int y_coor, int width, int height)
{
	Texture tmp;
	tmp.loadFromFile(fileName, IntRect(x_coor, y_coor, width, height));
	scr.push_back(tmp);
	// TODO: insert return statement here
	return scr;
}
