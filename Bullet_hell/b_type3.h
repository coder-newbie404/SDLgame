#ifndef B_TYPE3__H_
#define B_TYPE3__H_

#include <iostream>
#include <SDL.h>
#include <cstring>
#include "g_running.h"
#include "general_helper.h"

using namespace std;

struct Type3
{
    Bullet blst[16];
    SDL_Texture* image;

    Type3(int a, int b);

    void render(SDL_Renderer* renderer);

    void type3_move();

    bool inside(int minx, int miny, int maxx, int maxy);

    void reset();
};

#endif

