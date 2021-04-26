#include <iostream>
#include <SDL.h>
#include <cstring>
#include "o_button.h"

using namespace std;

void Button::render(SDL_Renderer* renderer)
{
    SDL_Rect filled_rect;
    filled_rect.x=x;
    filled_rect.y=y;
    filled_rect.w=w;
    filled_rect.h=h;
    SDL_RenderSetViewport(renderer, &filled_rect);
    SDL_RenderCopy(renderer, image, NULL, NULL);
}
