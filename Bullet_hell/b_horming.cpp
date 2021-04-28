#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <cstring>
#include <cmath>
#include "b_horming.h"

using namespace std;

void Horming::render(SDL_Renderer* renderer, Player p)
{
    int xdis = (x - p.x);
    int ydis = (y - p.y);
    int angle = atan2(ydis, xdis) * 180 / 3.14159265 - 90;
    SDL_Rect filled_rect;
    filled_rect.x=x;
    filled_rect.y=y;
    filled_rect.w=w;
    filled_rect.h=h;
    SDL_RenderSetViewport(renderer, &filled_rect);
    SDL_RenderCopyEx(renderer, image, NULL, NULL, angle, NULL, SDL_FLIP_NONE);
}

void Horming::horming_move(Player p)
{
    int xdis = abs(x - p.x);
    int ydis = abs(y - p.y);
    int b = (5*ydis) / sqrt(xdis * xdis + ydis * ydis);
    int a = sqrt(25 - b * b);
    if (x > p.x)
        x -= a;
    else if (x < p.x)
        x += a;
    else
        x = 0;
    if (y > p.y)
        y -= b;
    else if (y < p.y)
        y += b;
    else
        y = 0;
    fuel -= 1;
    if (fuel == 0)
    {
        x = rand()%(SCREEN_WIDTH - w);
        y = 0;
        fuel = rand()%900 - 200;
        if (fuel < 200)
            fuel = 200;
    }
}

bool Horming::dead(Player p1)
{
    if ((x > p1.x && x < p1.x + p1.box_size && y + h > p1.y && y + h < p1.y + p1.box_size) || (x + w > p1.x && x + w < p1.x + p1.box_size && y + h > p1.y && y + h < p1.y + p1.box_size))
        return true;
    return false;
}
