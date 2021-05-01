#include <iostream>
#include <SDL.h>
#include <cstring>
#include "o_button.h"

using namespace std;

void Button::render(SDL_Renderer* renderer)
{
    SDL_Rect filled_rect = {x, y, w, h};
    SDL_RenderSetViewport(renderer, &filled_rect);
    SDL_RenderCopy(renderer, image, NULL, NULL);
}
