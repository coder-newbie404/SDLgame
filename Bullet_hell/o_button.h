#ifndef O_BUTTON__H_
#define O_BUTTON__H_

#include <iostream>
#include <SDL.h>
#include <cstring>
#include "g_running.h"

using namespace std;

struct Button
{
    int x;
    int y;
    int w;
    int h;
    SDL_Texture* image;
    Button(int _x, int _y, int _w, int _h)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;
    }
    void render(SDL_Renderer* renderer);
};

#endif
