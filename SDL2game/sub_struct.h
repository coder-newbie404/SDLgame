#include <iostream>
#include <SDL.h>
#include <cstring>
#include <cmath>

struct Button
{
    int x;
    int y;
    int w = 100;
    int h = 60;
    Button(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    void render(SDL_Renderer* renderer)
    {
        SDL_Rect filled_rect;
        filled_rect.x=x;
        filled_rect.y=y;
        filled_rect.w=100;
        filled_rect.h=60;
        SDL_SetRenderDrawColor(renderer, 225, 204, 0, 255);
        SDL_RenderFillRect(renderer, &filled_rect);
    }
};


struct Player
{
    int scrwidth;
    int scrheight;
    int x = 200;
    int y = 700;
    int xdr = 5;
    int ydr = 0;
    int box_size = 10;
    int dir = 1;
    void render(SDL_Renderer* renderer)
    {
        SDL_Rect filled_rect;
        filled_rect.x=x;
        filled_rect.y=y;
        filled_rect.w=box_size;
        filled_rect.h=box_size;
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &filled_rect);
    }

    void move(int direc)
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
};


struct Rain
{
    int x;
    int y = 0;
    int sub;
    int xdr = rand()%10+5;
    int ydr = rand()%10+5;
    int box_size = 10;
    void render(SDL_Renderer* renderer)
    {
        SDL_Rect filled_rect;
        filled_rect.x=x;
        filled_rect.y=y;
        filled_rect.w=box_size;
        filled_rect.h=box_size;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &filled_rect);
    }

    void move()
    {
        if (sub == 2)
        {
            x+=xdr;
            y+=ydr;
        }
        else
        {
            x-=xdr;
            y+=ydr;
        }
    }
    bool inside(int minx, int miny, int maxx, int maxy)
    {
        return (minx<=x && miny<=y && maxx>=x+box_size && maxy>=y+box_size);
    }
};

struct Horming
{
    int x;
    int y;
    int xdir;
    int ydir;
    int box_size = 10;
    void render(SDL_Renderer* renderer)
    {
        SDL_Rect filled_rect;
        filled_rect.x=x;
        filled_rect.y=y;
        filled_rect.w=box_size;
        filled_rect.h=box_size;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &filled_rect);
    }

    void horming_move(Player p)
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
    }
    bool inside(int minx, int miny, int maxx, int maxy)
    {
        return (minx<=x && miny<=y && maxx>=x+box_size && maxy>=y+box_size);
    }
};

struct Sniper
{
    int x;
    int y = 5;
    int box_size = 10;
    void render(SDL_Renderer* renderer)
    {
        SDL_Rect warning;
        warning.x=x;
        warning.y=5;
        warning.w=10;
        warning.h=10;
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(renderer, &warning);

        SDL_Rect filled_rect;
        filled_rect.x=x;
        filled_rect.y=y;
        filled_rect.w=box_size;
        filled_rect.h=50;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &filled_rect);
    }
    void sniper_move()
    {
        y += 50;
    }
    bool inside(int minx, int miny, int maxx, int maxy)
    {
        return (minx<=x && miny<=y && maxx>=x+box_size && maxy>=y+box_size);
    }
};
