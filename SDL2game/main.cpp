#include <iostream>
#include <SDL.h>
#include <cstring>
#include "sub_item.h"
#include "sub_struct.h"
#include "sub_sys.h"

using namespace std;


void gamebegin(Button start_b, Button exit_b, bool &isend, SDL_Renderer* renderer, SDL_Window* window)
{
    while(isend)
    {
        SDL_SetRenderDrawColor(renderer, 204, 51, 255, 255);
        SDL_RenderClear(renderer);
        start_b.render(renderer);
        exit_b.render(renderer);

        SDL_RenderPresent(renderer);

        SDL_Event start;
        if (SDL_WaitEvent(&start) == 0)
            continue;
        if (start.type == SDL_QUIT)
            break;
        if (start.type == SDL_KEYDOWN && start.key.keysym.sym == SDLK_ESCAPE)
            break;
        if (start.type == SDL_MOUSEBUTTONDOWN)
        {
            int pos_x = start.button.x;
            int pos_y = start.button.y;
            if (start.button.button == SDL_BUTTON_LEFT)
            {
                if (pos_x > start_b.x && pos_x < start_b.x + start_b.w && pos_y > start_b.y && pos_y < start_b.y + start_b.h)
                {
                    isend = false;
                    break;
                }
                else if (pos_x > exit_b.x && pos_x < exit_b.x + exit_b.w && pos_y > exit_b.y && pos_y < exit_b.y + exit_b.h)
                {
                    quitSDL(window, renderer);
                    break;
                }
                else
                    isend = true;
            }
        }
    }
}


void gamerunning(Button start_b, Button exit_b, bool &ispause, bool &isend, SDL_Renderer* renderer, SDL_Window* window)
{
    SDL_Event e;

    Player p1;
    p1.scrheight = SCREEN_HEIGHT;
    p1.scrwidth = SCREEN_WIDTH;

    Rain rainlst[rand()%40+20];
    for (int i = 0; i < sizeof(rainlst) / sizeof(rainlst[0]); i++)
    {
        rainlst[i].x = rand()%(SCREEN_WIDTH - rainlst[i].box_size);
    }

    while (isend == false)
    {
        {

            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_RenderClear(renderer);

            if (ispause)
            {
                start_b.render(renderer);
                exit_b.render(renderer);
            }
            else
            {
                p1.render(renderer);

                for (int i = 0; i < sizeof(rainlst) / sizeof(rainlst[0]); i++)
                {
                    if (rainlst[i].inside(0,0,SCREEN_WIDTH,SCREEN_HEIGHT))
                    {
                        rainlst[i].render(renderer);
                    }
                    else
                    {
                        rainlst[i].x = rand()%796+5;
                        rainlst[i].y = 0;
                        rainlst[i].render(renderer);
                    }
                }
            }

            SDL_RenderPresent(renderer);


            if (ispause == false)
            {
                for (int i = 0; i < sizeof(rainlst) / sizeof(rainlst[0]); i++)
                {
                    rainlst[i].move();
                }
            }

            SDL_WaitEventTimeout(&e, 10);

            if (e.type == SDL_QUIT)
            {
                quitSDL(window, renderer);
                break;
            }

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
                    ispause = false;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                    ispause = true;

            if (ispause == false)
            {
                if (e.type == SDL_KEYDOWN)
                {
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_LEFT:
                            p1.move(1);
                            break;
                        case SDLK_RIGHT:
                            p1.move(2);
                            break;
                        case SDLK_DOWN:
                            p1.move(4);
                            break;
                        case SDLK_UP:
                            p1.move(3);
                            break;
                        default: break;
                    }
                }
            }

            for (int i = 0; i < sizeof(rainlst) / sizeof(rainlst[0]); i++)
            {
                if (p1.x >= rainlst[i].x && p1.y >= rainlst[i].y && p1.x < rainlst[i].x + rainlst[i].box_size && p1.y < rainlst[i].y + rainlst[i].box_size)
                {
                    isend = true;
                }
                if (p1.x + p1.box_size >= rainlst[i].x && p1.y >= rainlst[i].y && p1.x + p1.box_size < rainlst[i].x + rainlst[i].box_size && p1.y < rainlst[i].y + rainlst[i].box_size)
                {
                    isend = true;
                }
            }
        }
    }
}


void gameover(Button start_b, Button exit_b, bool &isend, SDL_Renderer* renderer, SDL_Window* window)
{

    while(isend)
    {
        SDL_SetRenderDrawColor(renderer, 255, 80, 80, 255);
        SDL_RenderClear(renderer);
        start_b.render(renderer);
        exit_b.render(renderer);

        SDL_RenderPresent(renderer);

        SDL_Event start;
        if (SDL_WaitEvent(&start) == 0) continue;
        if (start.type == SDL_QUIT) break;
        if (start.type == SDL_KEYDOWN && start.key.keysym.sym == SDLK_ESCAPE) break;
        if (start.type == SDL_MOUSEBUTTONDOWN)
        {
            int pos_x = start.button.x;
            int pos_y = start.button.y;
            if (start.button.button == SDL_BUTTON_LEFT)
            {
                if (pos_x > start_b.x && pos_x < start_b.x + start_b.w && pos_y > start_b.y && pos_y < start_b.y + start_b.h)
                {
                    isend = false;
                    break;
                }
                else if (pos_x > exit_b.x && pos_x < exit_b.x + exit_b.w && pos_y > exit_b.y && pos_y < exit_b.y + exit_b.h)
                {
                    quitSDL(window, renderer);
                    break;
                }
                else
                    isend = true;
            }
        }
    }
}


int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    Button start_b;
    Button exit_b;

    start_b.x = 200;
    start_b.y = 370;

    exit_b.x = 700;
    exit_b.y = 370;



    bool isend = true;
    bool ispause = false;

    gamebegin(start_b, exit_b, isend, renderer, window);

    while (isend == false)
    {
        gamerunning(start_b, exit_b, ispause, isend, renderer, window);

        gameover(start_b, exit_b, isend, renderer, window);
    }

    return 0;
}
