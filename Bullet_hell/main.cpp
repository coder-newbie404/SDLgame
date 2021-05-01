#include <iostream>
#include <SDL.h>
#include <cstring>
#include "g_menu.h"
#include "g_lb.h"
#include "g_name_input.h"
#include "g_running.h"
#include "g_restart.h"
#include "general_helper.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;

int main(int argc, char* argv[])
{
    init(window, renderer);

    int isend = 0;
    int tscore = 0;
    string name;

    while (true)
    {
        switch (isend)
        {
            case 0:
                gamebegin(window, renderer, isend);
                break;
            case 3:
                leaderBoard(window, renderer, isend);
                break;
            case 1:
                {
                    inputname(window, renderer, name);
                    gamerunning(window, renderer, isend, tscore);
                }
                break;
            case 2:
                {
                    gameover(window, renderer, isend, tscore, name);
                    highScore(name, tscore);
                }
                break;
        }
    }

    return 0;
}
