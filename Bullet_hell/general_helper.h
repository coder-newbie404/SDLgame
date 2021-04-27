#ifndef SYS__H_
#define SYS__H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cstring>
#include <sstream>
#include "b_normal.h"
#include "o_player.h"

using namespace std;

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 800;
const string WINDOW_TITLE = "Bullet Hell";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

bool init(SDL_Window* &window, SDL_Renderer* &renderer);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void rendersub(SDL_Renderer* renderer, SDL_Texture* bgr, int x, int y, int w, int h);

#endif // SYS__H_

