#include "Game.h"

int main()
{
    vector<int> mapIndex = {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0};
    Game game(mapIndex);
    game.run();

    return 0;
}