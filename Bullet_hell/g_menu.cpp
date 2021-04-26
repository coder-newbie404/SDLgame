#include <iostream>
#include <SDL.h>
#include <cstring>
#include "g_menu.h"
#include "o_button.h"
#include "sys.h"

using namespace std;

SDL_Surface* start_image = IMG_Load("res/play.png");
SDL_Surface* exit_image = IMG_Load("res/quit.png");
SDL_Surface* logo_image = IMG_Load("res/logo.png");
SDL_Surface* backgr_image = IMG_Load("res/mainmenu1.png");
SDL_Surface* amage = IMG_Load("res/a.png");


void gamebegin(SDL_Window* window, SDL_Renderer* renderer, int &isend)
{
    Button start_b(SCREEN_WIDTH - 200, 370, 150, 50);
    start_b.image = SDL_CreateTextureFromSurface(renderer, start_image);
    Button exit_b(SCREEN_WIDTH - 200, 570, 150, 50);
    exit_b.image = SDL_CreateTextureFromSurface(renderer, exit_image);
    Button logo(50, 50, 500, 250);
    logo.image = SDL_CreateTextureFromSurface(renderer, logo_image);
    SDL_Texture* bgr = SDL_CreateTextureFromSurface(renderer, backgr_image);
    SDL_Texture* amagetext = SDL_CreateTextureFromSurface(renderer, amage);

    while (isend == 0)
    {
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        rendersub(renderer, bgr, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        logo.render(renderer);

        SDL_Event start;
        if (start.type == SDL_MOUSEMOTION)
        {
            int pos_x = start.button.x + exit_b.x;
            int pos_y = start.button.y + exit_b.y;
            if (pos_x > start_b.x && pos_x < start_b.x + start_b.w && pos_y > start_b.y && pos_y < start_b.y + start_b.h)
            {
                rendersub(renderer, amagetext, start_b.x-5, start_b.y-5, start_b.w+10, start_b.h+10);
            }
            if (pos_x > exit_b.x && pos_x < exit_b.x + exit_b.w && pos_y > exit_b.y && pos_y < exit_b.y + exit_b.h)
            {
                rendersub(renderer, amagetext, exit_b.x-5, exit_b.y-5, exit_b.w+10, exit_b.h+10);
            }
        }

        start_b.render(renderer);
        exit_b.render(renderer);

        SDL_RenderPresent(renderer);

        if (SDL_WaitEvent(&start) == 0)
            continue;

        if (start.type == SDL_QUIT)
            quitSDL(window, renderer);

        if (start.type == SDL_MOUSEBUTTONDOWN)
        {
            int pos_x = start.button.x + exit_b.x;
            int pos_y = start.button.y + exit_b.y;
            if (start.button.button == SDL_BUTTON_LEFT)
            {
                if (pos_x > start_b.x && pos_x < start_b.x + start_b.w && pos_y > start_b.y && pos_y < start_b.y + start_b.h)
                {
                    isend = 1;
                    break;
                }
                else if (pos_x > exit_b.x && pos_x < exit_b.x + exit_b.w && pos_y > exit_b.y && pos_y < exit_b.y + exit_b.h)
                {
                    quitSDL(window, renderer);
                    break;
                }
            }
        }
    }
}
