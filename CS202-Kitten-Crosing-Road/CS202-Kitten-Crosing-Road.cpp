#include "Game.h"

int main()
{
    srand((unsigned)time(NULL));
    vector<int> mapIndex = {0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 0, 2};
    Game game(mapIndex);
    game.run();

    return 0;
}