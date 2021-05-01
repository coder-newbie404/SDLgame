#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "g_lb.h"
#include "general_helper.h"
#include "Ltexture.h"
#include "o_button.h"

using namespace std;

SDL_Surface* i_backmn = IMG_Load("res/backmenu.png");
SDL_Surface* i_bgrlb = IMG_Load("res/lbbk.png");
SDL_Surface* i_bk = IMG_Load("res/a.png");

void leaderBoard(SDL_Window* window, SDL_Renderer* renderer, int &isend)
{
    string namelst[10];
    int scorelst[10];

    ifstream fileInput;
    fileInput.open("res/leaderboard.txt");
	for (int i = 0; i < 10; i++)
    {
        fileInput >> namelst[i];
        fileInput >> scorelst[i];
    }
    fileInput.close();

    TTF_Font* gFont = TTF_OpenFont( "res/BlackOpsOne-Regular.ttf", 28 );

    Button backmn(SCREEN_WIDTH - 250, SCREEN_HEIGHT - 80, 240, 60);
    backmn.image = SDL_CreateTextureFromSurface(renderer, i_backmn);
    SDL_Texture* bgrmn = SDL_CreateTextureFromSurface(renderer, i_bgrlb);
    SDL_Texture* bk = SDL_CreateTextureFromSurface(renderer, i_bk);

    stringstream namescore;
    LTexture nameScoreTexture(renderer, gFont);
    SDL_Color textColor = {53, 49, 133, 255};

    SDL_Event e;

    while (isend == 3)
    {
        SDL_RenderClear(renderer);

        rendersub(renderer, bgrmn, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        for (int i = 0; i < 10; i++)
        {
            namescore.str( "" );
            if (i == 9)
                namescore << i + 1 << "   " << namelst[i];
            else
                namescore << i + 1 << "     " << namelst[i];
            nameScoreTexture.loadFromRenderedText( namescore.str().c_str(), textColor );
            nameScoreTexture.render(280, 140 + i * 60);

            namescore.str( "" );
            namescore << scorelst[i];
            nameScoreTexture.loadFromRenderedText( namescore.str().c_str(), textColor );
            nameScoreTexture.render(600, 140 + i * 60);
        }

        if (e.type == SDL_MOUSEMOTION)
        {
            int pos_x = e.button.x + backmn.x;
            int pos_y = e.button.y + backmn.y;
            if (pos_x > backmn.x && pos_x < backmn.x + backmn.w && pos_y > backmn.y && pos_y < backmn.y + backmn.h)
            {
                rendersub(renderer, bk, backmn.x-5, backmn.y-5, backmn.w+10, backmn.h+10);
            }
        }

        backmn.render(renderer);

        SDL_RenderPresent(renderer);

        SDL_WaitEventTimeout(&e, 10);

        if (e.type == SDL_QUIT)
        {
            quitSDL(window, renderer);
        }

        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            int pos_x = e.button.x + backmn.x;
            int pos_y = e.button.y + backmn.y;
            if (e.button.button == SDL_BUTTON_LEFT)
                if (pos_x > backmn.x && pos_x < backmn.x + backmn.w && pos_y > backmn.y && pos_y < backmn.y + backmn.h)
                {
                    isend = 0;
                    break;
                }
        }
    }
}
