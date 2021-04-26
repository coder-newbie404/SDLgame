#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <cstring>
#include "gbgr.h"

using namespace std;

void Background::grender(SDL_Renderer* renderer)
{
    rendersub(renderer, bgr1, 0, y1, SCREEN_WIDTH, SCREEN_HEIGHT);
    rendersub(renderer, bgr2, 0, y2, SCREEN_WIDTH, SCREEN_HEIGHT);
    y1 *= 5;
    y2 += 5;
    if (y1 == SCREEN_HEIGHT)
        y1 = 0;
    if (y2 == SCREEN_HEIGHT)
        y2 = 0;
}
