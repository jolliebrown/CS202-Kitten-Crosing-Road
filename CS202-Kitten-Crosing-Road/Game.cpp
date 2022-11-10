#include "Game.h"

const Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() : mWindow(VideoMode(1120, 800), "SFML Application", Style::Close), mStatisticsNumFrames(0), mStatisticsUpdateTime(), mView(sf::FloatRect(0, 0, 224, 160))
{
	tWorld.create(160, 20);
	tWorld.setRepeated(true);
	tWorld.loadFromFile("Media/Grass.png", IntRect(0, 0, 80, 20));
	world.setTexture(tWorld);
}

void Game::run()
{
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;
	while (mWindow.isOpen())
	{
		Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents()
{
	Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::KeyPressed:
			break;

		case Event::KeyReleased:
			break;

		case Event::Closed:
			mWindow.close();
			break;
		default:
			break;
		}
	}
}

void Game::update(Time elapsedTime)
{

}

void Game::render()
{
	mWindow.clear();
	mWindow.setView(mView);
	mWindow.draw(world);
	// draw sth here
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
