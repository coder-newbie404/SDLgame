#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <cstring>
#include "b_type3.h"

using namespace std;

Type3::Type3(int a, int b)
{
    for (int i = 0; i < 16; i++)
    {
        blst[i].x = a;
        blst[i].y = b;
    }
    blst[0].xdr = 0;
    blst[0].ydr = -4;
    blst[1].xdr = 1;
    blst[1].ydr = -3;
    blst[2].xdr = 2;
    blst[2].ydr = -2;
    blst[3].xdr = 3;
    blst[3].ydr = -1;
    blst[4].xdr = 4;
    blst[4].ydr = 0;
    blst[5].xdr = 3;
    blst[5].ydr = 1;
    blst[6].xdr = 2;
    blst[6].ydr = 2;
    blst[7].xdr = 1;
    blst[7].ydr = 3;
    blst[8].xdr = 0;
    blst[8].ydr = 4;
    blst[9].xdr = -1;
    blst[9].ydr = 3;
    blst[10].xdr = -2;
    blst[10].ydr = 2;
    blst[11].xdr = -3;
    blst[11].ydr = 1;
    blst[12].xdr = -4;
    blst[12].ydr = 0;
    blst[13].xdr = -3;
    blst[13].ydr = -1;
    blst[14].xdr = -2;
    blst[14].ydr = -2;
    blst[15].xdr = -1;
    blst[15].ydr = -3;
}

void Type3::type3_move()
{
    for (int i = 0; i < 16; i++)
    {
        blst[i].move();
    }
}

void Type3::render(SDL_Renderer* renderer)
{
    for (int i = 0; i < 16; i++)
    {
        blst[i].render(renderer);
    }
}

bool Type3::inside(int minx, int miny, int maxx, int maxy)
{
    for (int i = 0; i < 16; i++)
    {
        if (blst[i].inside(minx, miny, maxx, maxy))
            return true;
    }
    return false;
}

void Type3::reset()
{
    int a0 = rand()%(SCREEN_WIDTH - blst[0].w);
    int b0 = rand()%(SCREEN_HEIGHT - blst[0].h);
    for (int i = 0; i < 16; i++)
    {
        blst[i].x = a0;
        blst[i].y = b0;
    }
}

bool Type3::dead(Player p1)
{
    for (int i = 0; i < 16; i++)
        if (blst[i].dead(p1))
            return true;
    return false;
}
