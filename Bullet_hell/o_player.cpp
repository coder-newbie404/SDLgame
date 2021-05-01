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
            if (y > 10)
                y -= 10;
            break;
        case 2:
            if (x < scrwidth - box_size)
                x += 10;
            break;
        case 3:
            if (y < scrheight - box_size)
                y += 10;
            break;
        case 4:
            if (x > 10)
                x -= 10;
            break;
    }
}

void Player::render(SDL_Renderer* renderer)
{
    SDL_Rect filled_rect = {x, y, box_size, box_size};
    SDL_RenderSetViewport(renderer, &filled_rect);
    SDL_RenderCopyEx(renderer, image, NULL, NULL, 0, NULL, SDL_FLIP_NONE);
}
