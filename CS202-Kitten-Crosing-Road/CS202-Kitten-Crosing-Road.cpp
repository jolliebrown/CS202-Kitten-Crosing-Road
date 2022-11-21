#include "Game.h"

int main()
{
    srand(time(NULL));
    vector<int> mapIndex = {1, 1, 2, 0, 2, 1, 1, 1, 1, 1, 0, 2};
    Game game(mapIndex);
    game.run();

    return 0;
}