#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <cstring>
#include <sstream>
#include <fstream>
#include "general_helper.h"
#include "b_normal.h"
#include "o_player.h"

using namespace std;

bool init(SDL_Window* &window, SDL_Renderer* &renderer)
{
	bool success = true;

	SDL_Init( SDL_INIT_VIDEO );

    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    int imgFlags = IMG_INIT_PNG;
    IMG_Init( imgFlags );

    TTF_Init();

    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );

    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	return success;
}


void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void rendersub(SDL_Renderer* renderer, SDL_Texture* bgr, int x, int y, int w, int h)
{
    SDL_Rect filled_rect;
    filled_rect.x=x;
    filled_rect.y=y;
    filled_rect.w=w;
    filled_rect.h=h;
    SDL_RenderSetViewport(renderer, &filled_rect);
    SDL_RenderCopy(renderer, bgr, NULL, NULL);
}

void highScore(string name, int tscore)
{
    if ((name == "") || (name == " "))
        name = "Unknown";

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

    if (tscore > scorelst[9])
    {
        for (int i = 9; i >= 0; i--)
        {
            if (i == 0)
            {
                if (tscore > scorelst[i])
                {
                    scorelst[i] = tscore;
                    namelst[i] = name;
                }
            }
            else
            {
                if (tscore > scorelst[i])
                    if (tscore < scorelst[i - 1])
                    {
                        scorelst[i] = tscore;
                        namelst[i] = name;
                        tscore = 0;
                        break;
                    }
                    else
                    {
                        scorelst[i] = scorelst[i - 1];
                        namelst[i] = namelst[i - 1];
                    }

            }
        }
    }
    ofstream fileOutput;
    fileOutput.open("res/leaderboard.txt", ios::trunc );
    for (int i = 0; i < 10; i++)
    {
        fileOutput << namelst[i] << " " << scorelst[i] << endl;
    }
    fileInput.close();
}

