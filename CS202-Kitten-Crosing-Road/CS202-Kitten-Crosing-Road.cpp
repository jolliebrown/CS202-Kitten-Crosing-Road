#include "Game.h"

int main()
{
    srand(time(NULL));
    vector<int> mapIndex(0);
    for (int i = 0; i < 20; i++) mapIndex.push_back((rand() * 1) * (rand() + 1) % 3);
    Game game(mapIndex);
    game.run();

    // run menu
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
    return 0;
}