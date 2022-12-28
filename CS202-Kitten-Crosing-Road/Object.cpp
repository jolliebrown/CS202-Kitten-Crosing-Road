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

	load(num_text, "Media/Num 1px_brown.png", 0, 0, 60, 7, 6, 7);

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
	
	for (int i = 0; i < 6; i++)
	{
		systemButton[(MiniButton)i].first.loadFromFile("Media/System/" + button_name((MiniButton) i) + ".png");
		systemButton[(MiniButton)i].second.loadFromFile("Media/System/" + button_name((MiniButton) i) + "_here.png");

	}
	
	onePicLoad(still, "Media/System/Game Paused.png");
	onePicLoad(still, "Media/System/Score_board.png");
	onePicLoad(still, "Media/System/Game Over.png");
	onePicLoad(still, "Media/System/Win.png");

	fishCoinName[FishCoin::Bonus] = "Bonus";
	fishCoinName[FishCoin::Normal] = "Normal";
	fishCoinName[FishCoin::Stop] = "Stop";
	fishCoinName[FishCoin::Destroy] = "Destroy";
	int fishCoinNum = 4;

	menuListName[MenuList::Menu] = "Menu";
	menuListName[MenuList::Mode] = "Mode";
	menuListName[MenuList::Settings] = "Settings";
	menuListName[MenuList::Instruction] = "Instruction";
	menuListName[MenuList::Classic] = "Classic";
	menuListName[MenuList::ButtonSettings] = "ButtonSettings";
	int menuListNum = 6;
	int maxMenuNum = 10;

	for (int i = 0; i < fishCoinNum; i++)
	{
		fishCoin[(FishCoin)i].loadFromFile("Media/System/" + fishCoinName[(FishCoin)i] + ".png");
	}

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

	numFont.loadFromFile("Media/pixel-1px.ttf");

	for (int i = 0; i < menuListNum; i++)
	{
		for (int j = 0; j < maxMenuNum; j++)
		{
			pair<Texture, Texture> menu_tmp;
			if (menu_tmp.first.loadFromFile("Media/Scene/" + menuListName[(MenuList)i] + "/" + to_string(j) + ".png"))
			{
				menu_tmp.second.loadFromFile("Media/Scene/" + menuListName[(MenuList)i] + "/" + to_string(j) + "_here.png");
				menuTexture[(MenuList)i].push_back(menu_tmp);
			}
		}
	}

	onePicLoad(commonAsset, "Media/Scene/Menu/menuBackground.png");
	onePicLoad(commonAsset, "Media/Scene/Menu/otherSceneBackground.png");
	for (int i = 0; i < menuListNum; i++)
	{
		Texture menu_tmp;
		menu_tmp.loadFromFile("Media/Scene/" + menuListName[(MenuList)i] + "/" + menuListName[(MenuList)i] + ".png");
		commonAsset.push_back(menu_tmp);
	}
	onePicLoad(commonAsset, "Media/System/Home_here.png");
}

Object::Object(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit) : 
	window(window), 
	unit(unit),
	x(x_coor),
	y(y_coor)
{
	mAsset = &texture;
	asset.setTexture(*mAsset);
	asset.setPosition((float)x_coor, (float)y_coor);
}

Object::Object(RenderWindow& window, Texture& texture, int x_coor, int y_coor) : 
	window(window), 
	unit(unit),
	x(x_coor),
	y(y_coor)
{
	unit = 0;
	mAsset = &texture;
	asset.setTexture(*mAsset);
	asset.setPosition((float)x_coor, (float)y_coor);
}

Object::Object(const Object& scr) : 
	window(scr.window), 
	unit(scr.unit), 
	mAsset(scr.mAsset),
	x(scr.x),
	y(scr.y)
{
	asset.setTexture(*mAsset);
	asset.setPosition(x, y);
}

//Object::~Object()
//{
//	delete mAsset;
//}

Object& Object::operator=(Object& scr)
{
	if (this == &scr) return *this;

	this->unit = scr.unit;
	this->asset = scr.asset;
	this->x = scr.x; this->y = scr.y;
	swap(this->mAsset, scr.mAsset);
	return *this;
}

void Object::draw()
{
	if (insideView())
		window.draw(asset);
}

string button_name(const MiniButton& src)
{
	switch (src)
	{
	case MiniButton::Pause:
		return "Pause";
	case MiniButton::Play:
		return "Play";
	case MiniButton::Settings:
		return "Settings";
	case MiniButton::Home:
		return "Home";
	case MiniButton::Restart:
		return "Restart";
	case MiniButton::Next:
		return "Next";
	default:
		return "";
	}
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

bool Object::isCollided(Object& src) {
	
	//else return false;
	float curX = asset.getPosition().x + 10.f, curY = asset.getPosition().y + 16.f;
	float tempX = src.asset.getPosition().x - 10.f, tempY = src.asset.getPosition().y - 16.f;

	if (src.getBound().contains(curX, curY)) {
		return true;
	}
	/*if (getBound().contains(tempX, tempY)) {
		return true;
	}*/
	return false;

	/*
	int curX = asset.getPosition().x, curY = asset.getPosition().y;
	int carX = src.asset.getPosition().x, carY = src.asset.getPosition().y;
	if (abs(curX - carX) <= 12 && abs(curY - carY) <= 12) {
		return true;
	}
	return false;
	*/
}

bool Object::isCollidedSpecial(Object& src) {
	//return src.getBound().intersects(getBound());
	//else return false;
	float curX = asset.getPosition().x + 8.f, curY = asset.getPosition().y + 16.f;
	if (src.getBound().contains(curX, curY)) {
		return true;
	}
	curX = asset.getPosition().x + 8.f, curY = asset.getPosition().y + 8.f;
	if (src.getBound().contains(curX, curY)) {
		return true;
	}
	//curX = asset.getPosition().x + 8.f, curY = asset.getPosition().y;
	if (src.getBound().contains(curX, curY)) {
		return true;
	}
	return false;

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


void Object::changeAppearance(Texture& texture)
{
	mAsset = &texture;
	asset.setTexture(*mAsset);
}

bool Object::isHere(const Vector2f& mouse)
{
	if (asset.getGlobalBounds().contains(mouse)) return true;
	return false;
}

bool Info::isHere(const Vector2f& mouse)
{
	if (mText.getGlobalBounds().contains(mouse)) return true;
	return false;
}

void Object::setPos(const View& view)
{
	Vector2f view_cen = view.getCenter() + Vector2f(-view.getSize().x / 2, -view.getSize().y / 2);
	asset.setPosition(view_cen.x + x, view_cen.y + y);
}

void Object::changePos(int _x, int _y)
{
	x = _x;
	y = _y;
	asset.setPosition(x, y);
}

void Object::setTexture(Texture& texture)
{
	mAsset = &texture;
	asset.setTexture(*mAsset);
}

void Info::setPos(const View& view)
{
	Vector2f view_cen = view.getCenter() + Vector2f(-view.getSize().x / 2, -view.getSize().y / 2);
	mText.setPosition(view_cen.x + x, view_cen.y + y);
}

void Info::setStr(const string& s)
{
	mText.setString(s);
	int x1 = (x / 2) - mText.getLocalBounds().width / 2;
	int y1 = (x / 3 * 1) - mText.getLocalBounds().height / 2;
	mText.setPosition(x1, y1);
}

void Info::draw()
{
	window.draw(mText);
}

void Info::drawWithView(const View& view, const int& s)
{
	//mText.setString(convertScore(s));
	setPos(view);
	draw();
}

Info::Info(Font& _font, RenderWindow& window, const Color& color, int size, int x_coor, int y_coor) : 
	mFont(_font), 
	window(window),
	x(x_coor),
	y(y_coor)
{
	mText.setString("000");
	mText.setFillColor(color);
	mText.setFont(mFont);
	mText.setCharacterSize(size);
	mText.setPosition(x, y);
}
