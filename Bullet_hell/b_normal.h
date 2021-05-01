#ifndef B_NORMAL__H_
#define B_NORMAL__H_

#include <iostream>
#include <SDL.h>
#include <cstring>
#include "g_running.h"
#include "o_player.h"
#include "general_helper.h"


using namespace std;

struct Bullet
{
    int x;
    int y = 0;
    int xdr;
    int ydr;
    SDL_Texture* image;
    int w = 10;
    int h = 42;
    int angle = 0;
    int counter;
    void render(SDL_Renderer* renderer);

    void move();

    bool inside(int minx, int miny, int maxx, int maxy);

    bool dead(Player p1);
};

#endif

