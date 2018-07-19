#ifndef GAME_H
#define GAME_H
#include <windows.h>
#include "Lander.h"
#include "Ground.h"
#include "Info.h"

class Game
{
    public:
        Game();
        virtual ~Game();
        void render(HWND, HDC);
        void restart();
        void nextLevel();
        void gameLoop(HWND, HDC);
        bool checkCollision();
        void landed(bool);
        bool paused = false;
        bool levelEnd = false;
        bool mainMenu = true;
        int level = 0;
        int points = 0;
        POINT collisionPosition;
        Ground ground;
        Lander lander;
        Info info;
        char landingMessage [100];

};
static bool sound = true;
#endif // GAME_H
