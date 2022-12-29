#include "Game.h"
#include "other.h"

//void playSound(string fileName)
//{
//    PlaySound(LPCWSTR(fileName.c_str()), NULL, SND_SYNC);
//}

int main()
{
    /*SoundBuffer buffer;
    buffer.loadFromFile("Media/bgm.wav");
    Sound bgm;
    bgm.setBuffer(buffer);
    bgm.play();*/

    srand(time(NULL));
    Game game;
    game.run();
    return 0;
}