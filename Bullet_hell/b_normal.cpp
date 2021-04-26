#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <cstring>
#include "b_normal.h"

using namespace std;

void Bullet::render(SDL_Renderer* renderer)
{
    SDL_Rect filled_rect;
    filled_rect.x=x;
    filled_rect.y=y;
    filled_rect.w=w;
    filled_rect.h=h;
    SDL_RenderSetViewport(renderer, &filled_rect);
    SDL_RenderCopyEx(renderer, image, NULL, NULL, angle, NULL, SDL_FLIP_NONE);
}

void Bullet::move()
{
    x += xdr;
    y += ydr;
}

bool Bullet::inside(int minx, int miny, int maxx, int maxy)
{
    return (minx<=x && miny<=y && maxx>=x+w && maxy>=y+h);
}
