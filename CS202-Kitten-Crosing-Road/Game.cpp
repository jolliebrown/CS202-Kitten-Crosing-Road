#include "Game.h"

const Time Game::TimePerFrame = sf::seconds(1.f / 5.f);

Game::Game(vector<int>& mapIndex) : mWindow(VideoMode(1120, 800), "SFML Application", Style::Close), mStatisticsNumFrames(0), mStatisticsUpdateTime(), mView(sf::FloatRect(0, 0, 224, 160)), mWorld(mWindow, mapIndex), mPlayer(mWindow, mWorld.user[0], 104, 0, 16)
{
}

//void Game::run()
//{
//	Texture mUser;
//	mUser.loadFromFile("Media/Binh.png");
//	IntRect border(0, 0, 16, 16);
//	Sprite user(mUser, border);
//	Clock clock;
//	Time timeSinceLastUpdate = Time::Zero;
//	float dx = 0, dy = 0;
//	while (mWindow.isOpen())
//	{
//		Time elapsedTime = clock.restart();
//		timeSinceLastUpdate += elapsedTime;
//		while (timeSinceLastUpdate > TimePerFrame)
//		{
//			dx = dx > 224 ? 0 : dx + 1;
//			//user.setPosition(dx, dy);
//			timeSinceLastUpdate -= TimePerFrame;
//			border.left = (border.left + 16) % 48;
//			user.setTextureRect(border);
//			processEvents();
//			update(TimePerFrame);
//		}
//
//		updateStatistics(elapsedTime);
//		mWindow.clear();
//		mWindow.setView(mView);
//		mWorld.draw();
//		mWindow.draw(user);
//		mWindow.display();
//		//render();
//	}
//}

void Game::run()
{
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;
	int dx = 0, dy = 0;
	while (mWindow.isOpen())
	{
		Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			processEvents();
			update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents()
{

	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mPlayer.handleEvent(event, commands);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}

	mPlayer.handleRealtimeInput(commands);
}

void Game::update(Time elapsedTime)
{

}

void Game::render()
{
	mWindow.clear();
	mWindow.setView(mView);
	// draw sth here
	mWorld.draw();
	mPlayer.draw();
	mWindow.display();
}

void Game::updateStatistics(Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + to_string(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + to_string(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}
