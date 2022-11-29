#include "Object.h"

ListTextures::ListTextures()
{
	// load het asset vao day nha
	load(grass, "Media/Grass.png", 0, 0, 48, 32, BaseUnit);
	load(road, "Media/Road.png", 0, 0, 48, 18, BaseUnit + 2 * BaseUnit / 16);
	load(rail, "Media/Rail.png", 0, 0, 48, 18, BaseUnit + 2 * BaseUnit / 16);
	onePicLoad(car, "Media/car.png", 0, 0, 20, 10);
	onePicLoad(user, "Media/Binh.png");

	onePicLoad(light, "Media/Tlight_g.png");
	onePicLoad(light, "Media/Tlight_y.png");
	onePicLoad(light, "Media/Tlight_r.png");
}

Object::Object(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit) : 
	window(window), 
	mAsset(texture), 
	unit(unit)
{
	asset.setTexture(mAsset);
	asset.setPosition((float)x_coor, (float)y_coor);
}

Object::Object(RenderWindow& window, Texture& texture, int x_coor, int y_coor) : 
	window(window), 
	mAsset(texture), 
	unit(unit)
{
	unit = 0;
	asset.setTexture(mAsset);
	asset.setPosition((float)x_coor, (float)y_coor);
}

Object::Object(const Object& scr) : 
	window(scr.window), 
	unit(scr.unit), 
	mAsset(scr.mAsset)
{
	asset.setTexture(mAsset);
	float x_coor = scr.asset.getPosition().x;
	float y_coor = scr.asset.getPosition().y;
	asset.setPosition(x_coor, y_coor);
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

vector<Texture>& ListTextures::onePicLoad(vector<Texture>& scr, string fileName)
{
	Texture tmp;
	tmp.loadFromFile(fileName);
	scr.push_back(tmp);
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

bool Object::isCollided(const Object& src) {
	if (getBound().intersects(src.getBound())) return true;
	else return false;
	//if (bound.contains(src.asset.getPosition())) return true;
	//else return false;
	int curX = asset.getPosition().x, curY = asset.getPosition().y;
	int carX = src.asset.getPosition().x, carY = src.asset.getPosition().y;
	if (abs(curX - carX) <= 13 && abs(curY - carY) <= 13) {
		return true;
	}
	return false;
}

FloatRect Object::getBound() const
{
	return asset.getGlobalBounds();
}
