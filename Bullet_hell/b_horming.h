#ifndef B_HORMING__H_
#define B_HORMING__H_

#include <iostream>
#include <SDL.h>
#include <cstring>
#include "g_running.h"
#include "o_player.h"
#include "general_helper.h"

using namespace std;

struct Horming
{
    int x;
    int y;
    int w = 42;
    int h = 42;
    int fuel;
    SDL_Texture* image;

    void render(SDL_Renderer* renderer, Player p1);

    void horming_move(Player p);

    bool inside(int minx, int miny, int maxx, int maxy);

    bool dead(Player p1);
};

#endif
