#include <iostream>
#include <SDL.h>
#include <cstring>

struct Button
{
    int x;
    int y;
    int w = 100;
    int h = 60;
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
    int xdr = 0;
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
        x+=xdr;
        y+=ydr;
    }
    bool inside(int minx, int miny, int maxx, int maxy)
    {
        return (minx<=x && miny<=y && maxx>=x+box_size && maxy>=y+box_size);
    }
};

