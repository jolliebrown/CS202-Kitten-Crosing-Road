#include "SoundEffect.h"

SoundEffect::SoundEffect()
{
	bgm.openFromFile("Media/SFX/bgm.wav");
	bgm.setLoop(true);
	bgm.setVolume(30.0f);
	buffer[SFX::Intro].loadFromFile("Media/SFX/Intro.wav");
	buffer[SFX::Coin].loadFromFile("Media/SFX/Coin.wav");
	buffer[SFX::Move].loadFromFile("Media/SFX/Move.wav");
	buffer[SFX::Lose].loadFromFile("Media/SFX/Lose.wav");
	sfx[SFX::Intro].setBuffer(buffer[SFX::Intro]);
	sfx[SFX::Move].setBuffer(buffer[SFX::Move]);
	sfx[SFX::Coin].setBuffer(buffer[SFX::Coin]);
	sfx[SFX::Lose].setBuffer(buffer[SFX::Lose]);
	sfx[SFX::Move].setVolume(80.0f);
	sfx[SFX::Lose].setVolume(80.0f);
}

void SoundEffect::playEffect(const SFX& type)
{
	sfx[type].play();
}
