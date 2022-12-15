#include "Object.h"

ListTextures::ListTextures()
{
	// load het asset vao day nha
	load(car, "Media/Car.png", 0, 0, 72, 12, 24, 12);
	//onePicLoad(car, "Media/Car.png", 0, 0, 20, 10);
	onePicLoad(user, "Media/Binh.png");

	onePicLoad(light, "Media/Tlight_g.png");
	onePicLoad(light, "Media/Tlight_y.png");
	onePicLoad(light, "Media/Tlight_r.png");


	vector<Texture> tmp;
	load(tmp, "Media/Grass.png", 0, 0, 48, 32, BaseUnit);
	background.push_back(tmp);
	tmp.clear();
	onePicLoad(tmp, "Media/Road.png");
	background.push_back(tmp);
	tmp.clear();
	onePicLoad(tmp, "Media/Rail.png");
	background.push_back(tmp);
	tmp.clear();

	onePicLoad(pressed, "Media/System/Pause_here.png");
	onePicLoad(pressed, "Media/System/Pause1_here.png");
	onePicLoad(pressed, "Media/System/Settings_here.png");
	onePicLoad(pressed, "Media/System/Home_here.png");

	onePicLoad(unpressed, "Media/System/Pause.png");
	onePicLoad(unpressed, "Media/System/Pause1.png");
	onePicLoad(unpressed, "Media/System/Settings.png");
	onePicLoad(unpressed, "Media/System/Home.png");
	
	onePicLoad(still, "Media/System/Game Paused.png");

	Texture temTrainTexture;
	temTrainTexture.create(90 + 68 * 5, 15);
	Image temTrainImage;
	for (int i = 0; i < 5; ++i) {
		temTrainImage.loadFromFile("Media/Train1.png");
		temTrainTexture.update(temTrainImage, 68 * i, 0);
	}
	temTrainImage.loadFromFile("Media/Train0.png");
	temTrainTexture.update(temTrainImage, 68 * 5, 0);
	train.push_back(temTrainTexture);
}

Object::Object(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit) : 
	window(window), 
	mAsset(texture), 
	unit(unit),
	x(x_coor),
	y(y_coor)
{
	asset.setTexture(mAsset);
	asset.setPosition((float)x_coor, (float)y_coor);
}

Object::Object(RenderWindow& window, Texture& texture, int x_coor, int y_coor) : 
	window(window), 
	mAsset(texture), 
	unit(unit),
	x(x_coor),
	y(y_coor)
{
	unit = 0;
	asset.setTexture(mAsset);
	asset.setPosition((float)x_coor, (float)y_coor);
}

Object::Object(const Object& scr) : 
	window(scr.window), 
	unit(scr.unit), 
	mAsset(scr.mAsset),
	x(scr.x),
	y(scr.y)
{
	asset.setTexture(mAsset);
	asset.setPosition(x, y);
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
	if (insideView())
		window.draw(asset);
}

vector<Texture>& ListTextures::load(vector<Texture>& scr, string fileName, int x_coor, int y_coor, int width, int height, int x, int y)
{
	scr.clear();
	for (int i = 0; (i * x + x_coor) < width; i++)
	{
		for (int j = 0; (j * y + y_coor) < height; j++)
		{
			Texture tmp;
			tmp.loadFromFile(fileName, IntRect(i * x + x_coor, j * y + y_coor, x, y));
			scr.push_back(tmp);
		}
	}
	// TODO: insert return statement here
	return scr;
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
	//if (getBound().intersects(src.getBound())) return true;
	//else return false;
	float curX = asset.getPosition().x + 0.5, curY = asset.getPosition().y + 15.f;
	
	if (src.getBound().contains(curX, curY)) {
		cout << src.getBound().left << " " << src.getBound().top << " " << src.getBound().left+ src.getBound().width<< " " << src.getBound().top + src.getBound().height << endl;
		//cout << curX << " " << curY << endl;
		return true;
	}
	else return false;

	/*
	int curX = asset.getPosition().x, curY = asset.getPosition().y;
	int carX = src.asset.getPosition().x, carY = src.asset.getPosition().y;
	if (abs(curX - carX) <= 12 && abs(curY - carY) <= 12) {
		return true;
	}
	return false;
	*/
}

FloatRect Object::getBound() const
{
	return asset.getGlobalBounds();
}

bool Object::insideView() {
	//FloatRect viewRect= window.getView().getViewport();
	//if (getBound().intersects(viewRect)) return true;
	//else return false;
	Vector2f viewPosition = window.getView().getCenter();
	float curX = asset.getPosition().x, curY = asset.getPosition().y - 20;
	//if (curX < 0 || curX > BaseUnit * 14.f)
		//return false;
	if (curY > viewPosition.y + BaseUnit * 4.f)
		return false;
	if (curY < viewPosition.y - BaseUnit * 8.f)
		return false;
	return true;
}

bool Object::gameContinue() {
	//return Game.gameCon
	return true;
}

void Object::changeAppearance(Texture& texture)
{
	mAsset = texture;
}

bool Object::isHere(const Vector2f& mouse)
{
	if (asset.getGlobalBounds().contains(mouse)) return true;
	return false;
}

void Object::setPos(View& view)
{
	Vector2f view_cen = view.getCenter() + Vector2f(-view.getSize().x / 2, -view.getSize().y / 2);
	asset.setPosition(view_cen.x + x, view_cen.y + y);
}

