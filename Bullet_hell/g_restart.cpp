#include <iostream>
#include <SDL.h>
#include <cstring>
#include "g_restart.h"
#include "o_button.h"
#include "score.h"
#include "Ltexture.h"
#include "general_helper.h"


using namespace std;

SDL_Surface* deascene = IMG_Load("res/crash.png");
SDL_Surface* i_restart = IMG_Load("res/restart.png");
SDL_Surface* i_quit = IMG_Load("res/quit.png");
SDL_Surface* i_bkmenu = IMG_Load("res/backmenu.png");
SDL_Surface* i_hover = IMG_Load("res/a.png");



void gameover(SDL_Window* window, SDL_Renderer* renderer, int &isend, int &tscore, string &name)
{
    TTF_Font* gFont = TTF_OpenFont( "res/BlackOpsOne-Regular.ttf", 72 );

    Button restart_b(5, 700, 210, 60);
    restart_b.image = SDL_CreateTextureFromSurface(renderer, i_restart);
    Button gexit_b(1350, 700, 210, 72);
    gexit_b.image = SDL_CreateTextureFromSurface(renderer, i_quit);
    Button bmn(1280, 500, 280, 72);
    bmn.image = SDL_CreateTextureFromSurface(renderer, i_bkmenu);
    SDL_Texture* dea = SDL_CreateTextureFromSurface(renderer, deascene);
    SDL_Texture* atext = SDL_CreateTextureFromSurface(renderer, i_hover);

    stringstream pilot;
    stringstream timeText;
    LTexture PilotTexture(renderer, gFont);
    LTexture TimeTextTexture(renderer, gFont);
    SDL_Color textColor = {200, 200, 200, 255};
    timeText.str( "" );
    timeText << "SCORE:  " << tscore;
    TimeTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor );
    pilot.str("");
    pilot << "PILOT: " << name;
    PilotTexture.loadFromRenderedText( pilot.str().c_str(), textColor );

    while(isend)
    {
        SDL_RenderClear(renderer);
        rendersub(renderer, dea, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        TimeTextTexture.render( 5, 600);
        PilotTexture.render( 5, 500);

        SDL_Event start;
        if (start.type == SDL_MOUSEMOTION)
        {
            int pos_x = start.button.x + gexit_b.x;
            int pos_y = start.button.y + gexit_b.y;
            if (pos_x > restart_b.x && pos_x < restart_b.x + restart_b.w && pos_y > restart_b.y && pos_y < restart_b.y + restart_b.h)
            {
                rendersub(renderer, atext, restart_b.x-5, restart_b.y-5, restart_b.w+10, restart_b.h+10);
            }
            if (pos_x > bmn.x && pos_x < bmn.x + bmn.w && pos_y > bmn.y && pos_y < bmn.y + bmn.h)
            {
                rendersub(renderer, atext, bmn.x-5, bmn.y-5, bmn.w+10, bmn.h+10);
            }
            if (pos_x > gexit_b.x && pos_x < gexit_b.x + gexit_b.w && pos_y > gexit_b.y && pos_y < gexit_b.y + gexit_b.h)
            {
                rendersub(renderer, atext, gexit_b.x-5, gexit_b.y-5, gexit_b.w+10, gexit_b.h+10);
            }
        }

        bmn.render(renderer);
        restart_b.render(renderer);
        gexit_b.render(renderer);

        SDL_RenderPresent(renderer);

        if (SDL_WaitEvent(&start) == 0) continue;

        if (start.type == SDL_QUIT)
            quitSDL(window, renderer);

        if (start.type == SDL_MOUSEBUTTONDOWN)
        {
            int pos_x = start.button.x + gexit_b.x;
            int pos_y = start.button.y + gexit_b.y;
            if (start.button.button == SDL_BUTTON_LEFT)
            {
                if (pos_x > restart_b.x && pos_x < restart_b.x + restart_b.w && pos_y > restart_b.y && pos_y < restart_b.y + restart_b.h)
                {
                    isend = 1;
                    break;
                }
                else if (pos_x > gexit_b.x && pos_x < gexit_b.x + gexit_b.w && pos_y > gexit_b.y && pos_y < gexit_b.y + gexit_b.h)
                {
                    quitSDL(window, renderer);
                    break;
                }
                else if (pos_x > bmn.x && pos_x < bmn.x + bmn.w && pos_y > bmn.y && pos_y < bmn.y + bmn.h)
                {
                    isend = 0;
                    break;
                }
            }
        }
    }
}
