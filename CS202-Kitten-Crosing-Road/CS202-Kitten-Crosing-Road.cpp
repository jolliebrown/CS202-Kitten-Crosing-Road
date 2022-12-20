#include "Game.h"
#include "other.h"
int main()
{
    srand(time(NULL));
    /*RenderWindow window(VideoMode(BaseUnit * 70, BaseUnit * 50), "SFML Application", Style::Close);
    vector<Scene*> scene;
    Scene* menu = new Menu(window);
    scene.push_back(menu);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
            scene[scene.size() - 1]->handleEvent(event, scene, mouse);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        scene[scene.size() - 1]->draw();
        window.display();
    }*/
    //vector<int> mapIndex(0);
    //mapIndex = generateRangeLanes(1, 30);
    ///*for (int i = 0; i < 2; i++) mapIndex.push_back(0);*/
    //
    ////mapIndex.push_back(1);
    Game game;
    game.run();

    // run menu
    
    return 0;
}