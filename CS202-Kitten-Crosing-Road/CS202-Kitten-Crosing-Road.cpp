#include "Game.h"

int main()
{
    srand(time(NULL));
    vector<int> mapIndex(0);
    for (int i = 0; i < 50; i++) mapIndex.push_back((rand() * 1) * (rand() + 1) % 3);
    Game game(mapIndex);
    game.run();

    return 0;
}