#include "Game.h"

const Time Game::TimePerFrame = sf::seconds(1.f / 30.0f);

Game::Game() :
	mWindow(VideoMode(BaseUnit * 70, BaseUnit * 50), "SFML Application", Style::Close),
	mStatisticsNumFrames(0), mStatisticsUpdateTime(), mView(sf::FloatRect(0, 0, BaseUnit * 14, BaseUnit * 10)),
	mWorld(mWindow, 1, "EndLessMap"), mPlayer(mWindow, mWorld.user, 120 / BaseUnit * BaseUnit, -40, BaseUnit),
	gameSystem(mView, mWindow, true)
{
	cerr << "Game default constructor\n";
	cur_img.loadFromFile("Media/mouse_paw.png");
	cur_clicked.loadFromFile("Media/mouse_clicked.png");
	gameSystem.setState(GameState::Menu);
	
	ifstream is("EndLessMap\\savePlayer.txt");
	float isDead, playerX, playerY, viewX, viewY;
	is >> isDead >> playerX >> playerY >> viewX >> viewY;
	mPlayer.setPosition(playerX, playerY);
	mView.setCenter(viewX, viewY);
	mWindow.setView(mView);
}
bool Game::gameRestart() {
	mView.reset(sf::FloatRect(0, signMap * BaseUnit * 2, BaseUnit * 14, BaseUnit * 10));
	mPlayer.setIdPlayer(0);
	mPlayer.setPos(mView);
	mWorld.worldRestart();
	gameSystem.setState(GameState::Continue);
	return true;
}
Game::~Game()
{
	saveMap("EndLessMap");
	cerr << "Saved successfully\n";
}

bool Game::gameLose() {
	for (int i = 0; i < 6; i++) {
		sleep(sf::milliseconds(100));
		int sign = 1;
		if (i % 2 == 0) sign = 1;
		else sign = -1;
		mView.rotate(10 * sign);
		render();
	}
	return true;
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
		gameSystem.setState(GameState::Lose);
		gameLose();
	}
	if (mPlayer.getPosition().second > viewPosition.y + BaseUnit * 4.f - 4.f) {
		mPlayer.setIdPlayer(-1);
		gameSystem.setState(GameState::Lose);
		gameLose();
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

void Game::saveFile()
{
	ofstream fout(FileName[3]);
	// save info parameters
	gameSystem.writeFile(fout);
	// save map
	ofstream fout2(FileName[0]);
	mWorld.writeFile(fout2);
	// save high score
	ofstream fout3(FileName[1]);
	ofstream fout4(FileName[2]);
	gameSystem.writeHighScore(fout3);
	gameSystem.writeFishboost(fout4);
	fout.close();
	fout4.close();
	fout2.close();
	fout3.close();
}

void Game::saveMap(string folderName) 
{
	mWorld.saveMap(folderName);
	ofstream os(folderName + "\\savePlayer.txt");
	os << mPlayer.idPlayer << '\n';
	os << mPlayer.getPosition().first << ' ' << mPlayer.getPosition().second << '\n';
	os << mView.getCenter().x << ' ' << mView.getCenter().y << '\n';
}

void Game::run()
{
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;
	//mView.setCenter(mPlayer.getPosition().first, mPlayer.getPosition().second - 65);
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
			mPlayer.handleEvent(event, gameSystem, mWorld);
		}
		gameSystem.handleEvent(event, mouse);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
	if (gameSystem.gameContinue()) {
		mWorld.processEvent(gameSystem, mPlayer);
		mWorld.handleEvent(mWindow, mView);
		mPlayer.handleEvent(event, gameSystem, mWorld);
	}
	if (gameSystem.gameRestart()) {
		gameRestart();
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
	mWorld.draw(true);
	gameSystem.drawFish();
	//cout << mouse.x << " " << mouse.y << endl;
	mWorld.draw(false);
	mPlayer.draw();
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