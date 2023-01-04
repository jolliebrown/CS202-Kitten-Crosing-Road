#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "SoundEffect.h"

const int BaseUnit = 16;
const int TimeMove = 361;
const int signMap = -1;

using namespace sf;
using namespace std;

enum class Environment
{
	Grass,
	Road,
	Rail
};

enum class MiniButton
{
	Pause,
	Play,
	Settings,
	Home,
	Restart,
	Next
};

enum class FishCoin
{
	Normal,
	Stop,
	Destroy,
	Bonus
};

enum class MenuList
{
	Menu,
	Mode,
	Classic,
	Settings,
	SoundSettings,
	ButtonSettings,
	Instruction
};
string					button_name(const MiniButton& src);
// store all textures that need to be loaded
class ListTextures
{
public:
							ListTextures();
private: 
	vector<Texture>&		load(vector<Texture>& scr, string fileName, int x_coor, int y_coor, int width, int height, int x, int y);
	vector<Texture>&		load(vector<Texture>& scr, string fileName, int x_coor, int y_coor, int width, int height, int unit);
	vector<Texture>&		onePicLoad(vector<Texture>& scr, string fileName);
	vector<Texture>&		onePicLoad(vector<Texture>& scr, string fileName, int x_coor, int y_coor, int width, int height);
protected:
	vector<Texture>			grass;
	vector<Texture>			road;
	vector<Texture>			rail;
	vector<vector<Texture>> background;

	// menu

	// pictures that many scenes will use
	vector<Texture>			commonAsset;
	// pictures for individual scene
	map <MenuList, string>  menuListName;
	map <MenuList, vector<pair<Texture, Texture>>> menuTexture;
public:
	vector<Texture>			obstacle[2];
	vector<Texture>			car;
	vector<Texture>			user;
	vector<Texture>			light;
	vector<Texture>			tlight;
	vector<Texture>			train;
	Font					numFont;

	// button
	map < MiniButton, pair<Texture, Texture>> systemButton;
	map <FishCoin, string> fishCoinName;
	map<FishCoin, Texture> fishCoin;
	vector<Texture>			still;
	
	vector<Texture>			num_text;
};

// dung cho 1 cai tile nao do (vi du: background, car, user, ...)
class Object
{
public:
	Object(RenderWindow& window, Texture& texture, int x_coor, int y_coor, int unit);
	Object(RenderWindow& window, Texture& texture, int x_coor, int y_coor);
	Object(const Object& scr);
	Object&					operator=(Object& scr);
	//~Object();
	void					draw();
	bool isCollided(Object& src);
	bool isCollidedSpecial(Object& src);
	//const bool isCollided(const Object& src) const;
	//FloatRect				getBound();
	FloatRect				getBound() const;
	bool					insideView();
	void					changeAppearance(Texture& texture);
	bool					isHere(const Vector2f& mouse);
	void					setPos(const View& view);
	void					changePos(int _x, int _y);
	void					setTexture(Texture& texture);
private:
	RenderWindow&			window;
	Texture*				mAsset;
protected:
	int						unit;
	Sprite					asset;
	int	x, y;
};

class Info
{
private:
	Font&					mFont;
	RenderWindow&			window;
	Text					mText;
	int x, y;
public:
	Info(Font& _font, RenderWindow& window, const Color& color, int size, int x_coor, int y_coor);
	bool					isHere(const Vector2f& mouse);
	void					setPos(const View& view);
	void					setStr(const string& s);
	void					draw();
	void					drawWithView(const View& view, const int& s);
};

string convertScore(int a);