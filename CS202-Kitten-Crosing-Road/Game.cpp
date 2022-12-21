#include "Game.h"

const Time Game::TimePerFrame = sf::seconds(1.f / 30.0f);

Game::Game() :
	mWindow(VideoMode(BaseUnit * 70, BaseUnit * 50), "SFML Application", Style::Close),
	mStatisticsNumFrames(0), mStatisticsUpdateTime(), mView(sf::FloatRect(0, 0, BaseUnit * 14, BaseUnit * 10)),
	mWorld(mWindow), mPlayer(mWindow, mWorld.user[0], 120, -30, BaseUnit),
	gameSystem(mView, mWindow)
{
	cur_img.loadFromFile("Media/mouse_paw.png");
	cur_clicked.loadFromFile("Media/mouse_clicked.png");
}
void Game::viewScroll(View& mView, Player& mPlayer){
	if (mPlayer.idPlayer == -1 || gameSystem.gameContinue() == false) return;
	viewPosition = mView.getCenter();
	viewPosition.x = max(BaseUnit * 8.f - 4.f, min(BaseUnit * 22.f, mPlayer.getPosition().first));
	viewPosition.y -= 0.01f;
	if (viewPosition.y > mPlayer.getPosition().second)
		viewPosition.y = mPlayer.getPosition().second;
	//viewPosition.y = max(viewPosition.y, 0.f);
	viewPosition.y = min(viewPosition.y, BaseUnit * 10.f);
	mView.setCenter(viewPosition);
	if (mPlayer.getPosition().first < 0 || mPlayer.getPosition().first > BaseUnit * 29.f) {
		mPlayer.setIdPlayer(-1);
		gameSystem.setLose();
	}
	if (mPlayer.getPosition().second > viewPosition.y + BaseUnit * 4.f - 4.f) {
		mPlayer.setIdPlayer(-1);
		gameSystem.setLose();
	}
}

void Game::setCur(const Event& event)
{
	if (event.type == Event::MouseButtonPressed)
	{
		cursor.loadFromPixels(cur_clicked.getPixelsPtr(), cur_img.getSize(), Vector2u(5, 6));
	}
	else
	{
		cursor.loadFromPixels(cur_img.getPixelsPtr(), cur_img.getSize(), Vector2u(5, 6));
	}
	mWindow.setMouseCursor(cursor);
}

void Game::run()
{
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;
	mView.setCenter(mPlayer.getPosition().first, mPlayer.getPosition().second - 35);
	//viewPosition.x = mPlayer.getPosition().first;
	//viewPosition.y = mPlayer.getPosition().second;
	int dx = 0, dy = 0;
	while (mWindow.isOpen())
	{
		mouse = mWindow.mapPixelToCoords(Mouse::getPosition(mWindow));
		Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		//while (timeSinceLastUpdate > TimePerFrame)
		//{
		//	//cout << count << endl;
		//	processEvents();
		//	update(TimePerFrame);
		//	timeSinceLastUpdate -= TimePerFrame;
		//}
		processEvents();
		//update(TimePerFrame);
		render();
		//updateStatistics(elapsedTime);
		
	}
}

void Game::processEvents()
{
	//cout << mPlayer.getPosition().first << " " << mPlayer.getPosition().second << endl;
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		setCur(event);
		if (gameSystem.gameContinue()) {
			mPlayer.handleEvent(event, gameSystem);
		}
		gameSystem.handleEvent(event, mouse);
		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
	if (gameSystem.gameContinue()) {

		mPlayer.handleRealtimeInput();
		//gameSystem
		mWorld.processEvent(gameSystem, mPlayer);
		mPlayer.handleEvent(event, gameSystem);
		mWorld.handleEvent(mWindow, mView);
		
	}
	
}

void Game::update(Time elapsedTime)
{

}

void Game::render()
{
	mWindow.clear();
	viewScroll(mView, mPlayer);
	//mView.setCenter(mPlayer.getPosition().first, mPlayer.getPosition().second);
	mWindow.setView(mView);
	// draw sth here
	mWorld.draw();
	mPlayer.draw();
	//cout << mouse.x << " " << mouse.y << endl;
	gameSystem.draw(mouse);
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

bool inCurrentView(Vector2f);
bool Game::gameContinue() {
	return gameSystem.gameContinue();
}