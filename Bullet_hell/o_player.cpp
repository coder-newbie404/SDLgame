#include <iostream>
#include <SDL.h>
#include <cstring>
#include "o_player.h"

using namespace std;

void Player::move(int direc)
{
    switch (direc)
    {
        case 1:
            if (x == 0)
                xdr = 0;
            else
                xdr = -10;
            ydr = 0;
            break;
        case 2:
            if (x == scrwidth - box_size)
                xdr = 0;
            else
                xdr = 10;
            ydr = 0;
            break;
        case 3:
            if (y == 0)
                ydr = 0;
            else
                ydr = -10;
            xdr = 0;
            break;
        case 4:
            if (y == scrheight - box_size)
                ydr = 0;
            else
                ydr = 10;
            xdr = 0;
            break;
    }
    x+=xdr;
    y+=ydr;
}

void Player::render(SDL_Renderer* renderer)
{
    SDL_Rect filled_rect;
    filled_rect.x=x;
    filled_rect.y=y;
    filled_rect.w=box_size;
    filled_rect.h=box_size;
    SDL_RenderSetViewport(renderer, &filled_rect);
    SDL_RenderCopyEx(renderer, image, NULL, NULL, 0, NULL, SDL_FLIP_NONE);
}
