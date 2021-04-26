#include <iostream>
#include <SDL.h>
#include <cstring>
#include "g_menu.h"
#include "g_running.h"
#include "g_restart.h"
#include "general_helper.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;

int main(int argc, char* argv[])
{

    //initSDL(window, renderer);
    if (!init(window, renderer))
        printf("init window fail");

    int isend = 0;

    while (true)
    {
        switch (isend)
        {
            case 0:
                gamebegin(window, renderer, isend);
                break;
            case 1:
                gamerunning(window, renderer, isend);
                break;
            case 2:
                gameover(window, renderer, isend);
                break;
        }
    }

    return 0;
}
