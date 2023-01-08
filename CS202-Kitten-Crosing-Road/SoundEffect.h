#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace sf;
using namespace std;

enum class SFX
{
	Clicked,
	Move,
	Win,
	Lose,
	Car,
	Train,
	Light,
	Intro,
	Coin,
	Road
};

class SoundEffect
{
public: 
    SoundEffect();
    void	playEffect(const SFX& type);
    Music	bgm, road_bgm;
private:
    map<SFX, SoundBuffer> buffer;
    map<SFX, Sound> sfx;
};

