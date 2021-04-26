#ifndef GBGR__H
#define GBGR__H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <cstring>
#include "sys.h"

using namespace std;

struct Background
{
    int y1 = 0;
    int y2 = -SCREEN_HEIGHT;
    SDL_Texture* bgr1;
    SDL_Texture* bgr2;

    void grender(SDL_Renderer* renderer);
};
#endif

