#ifndef O_PLAYER__H_
#define O_PLAYER__H_

#include <iostream>
#include <SDL.h>
#include <cstring>

using namespace std;

struct Player
{
    int scrwidth;
    int scrheight;
    int x;
    int y = 700;
    int xdr;
    int ydr;
    int box_size = 50;
    int dir = 1;
    SDL_Texture* image;

    Player(int _x, int _scrheight, int _scrwidth)
    {
        x = _x;
        scrheight = _scrheight;
        scrwidth = _scrwidth;
    }

    void render(SDL_Renderer* renderer);


    void move(int direc);
};
#endif

