#include <iostream>
#include <SDL.h>
#include <cstring>
#include "sub_item.h"
#include "sub_struct.h"
#include "sub_sys.h"

using namespace std;


void gameover(bool &isend, SDL_Renderer* renderer, SDL_Window* window)
{
    while(isend)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        SDL_Event start;
        if (SDL_WaitEvent(&start) == 0) continue;
        if (start.type == SDL_QUIT) break;
        if (start.type == SDL_KEYDOWN)
        {
        	switch (start.key.keysym.sym)
            {
                case SDLK_n:
        		    quitSDL(window, renderer);
        		    break;
        		case SDLK_y:
                    isend = false;
                    break;
            }
        }
    }
}


void gamerunning(bool &isend, SDL_Renderer* renderer, SDL_Window* window)
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
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderClear(renderer);

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
                rainlst[i].y = 5;
                rainlst[i].render(renderer);
            }
        }

        SDL_RenderPresent(renderer);


        for (int i = 0; i < sizeof(rainlst) / sizeof(rainlst[0]); i++)
        {
            rainlst[i].move();
        }

        SDL_WaitEventTimeout(&e, 10);

        if (e.type == SDL_QUIT)
            break;
        if (e.type == SDL_KEYDOWN)
        {
        	switch (e.key.keysym.sym)
        	{
        		case SDLK_ESCAPE:
        		    quitSDL(window, renderer);
        		    break;
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

        for (int i = 0; i < sizeof(rainlst) / sizeof(rainlst[0]); i++)
        {
            if (p1.x >= rainlst[i].x && p1.y >= rainlst[i].y && p1.x < rainlst[i].x + rainlst[i].box_size && p1.y < rainlst[i].y + rainlst[i].box_size)
            {
                cout << "End game";
                isend = true;
            }
            if (p1.x + p1.box_size >= rainlst[i].x && p1.y >= rainlst[i].y && p1.x + p1.box_size < rainlst[i].x + rainlst[i].box_size && p1.y < rainlst[i].y + rainlst[i].box_size)
            {
                cout << "End game";
                isend = true;
            }
        }
    }
}


void gamebegin(bool &isend, SDL_Renderer* renderer, SDL_Window* window)
{
    while(isend)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        SDL_Event start;
        if (SDL_WaitEvent(&start) == 0) continue;
        if (start.type == SDL_QUIT) break;
        if (start.type == SDL_KEYDOWN)
        {
        	switch (start.key.keysym.sym)
            {
                case SDLK_n:
        		    quitSDL(window, renderer);
        		    break;
        		case SDLK_y:
                    isend = false;
                    break;
            }
        }
    }
}


int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    bool isend = true;

    gamebegin(isend, renderer, window);

    while (isend == false)
    {
        gamerunning(isend, renderer, window);

        gameover(isend, renderer, window);
    }

    quitSDL(window, renderer);
    return 0;
}
