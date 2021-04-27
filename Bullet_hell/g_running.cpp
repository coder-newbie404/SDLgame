#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_vulkan.h>
#include <cstring>
#include <sstream>
#include "g_running.h"
#include "o_button.h"
#include "b_normal.h"
#include "b_type3.h"
#include "b_horming.h"
#include "o_player.h"
#include "general_helper.h"
#include "score.h"
#include "Ltexture.h"

using namespace std;

SDL_Surface* i_bul = IMG_Load("res/bullet.png");
SDL_Surface* i_horm = IMG_Load("res/horming.png");
SDL_Surface* i_pla = IMG_Load("res/player.png");
SDL_Surface* i_bgr = IMG_Load("res/background.png");
SDL_Surface* i_pau = IMG_Load("res/mainmenu.png");
SDL_Surface* i_resu = IMG_Load("res/resume.png");
SDL_Surface* i_qui = IMG_Load("res/quit.png");
SDL_Surface* i_restr = IMG_Load("res/restart.png");
SDL_Surface* i_red = IMG_Load("res/a.png");



void gamerunning(SDL_Window* window, SDL_Renderer* renderer, int &isend, int &tscore)
{
    TTF_Font* gFont = TTF_OpenFont( "lazy.ttf", 28 );


    Button remuse_b(SCREEN_WIDTH - 200, 370, 120, 60);
    Button restart(SCREEN_WIDTH - 200, 570, 120, 60);
    Button bkmn(SCREEN_WIDTH - 200, 770, 120, 60);
    Player p1(200, SCREEN_HEIGHT, SCREEN_WIDTH);
    Bullet rainlst[rand()%50 + 10];
    Type3 firstshot(rand()%(SCREEN_WIDTH - firstshot.blst[0].w), rand()%(SCREEN_HEIGHT - firstshot.blst[0].h));
    Horming horm[8];

    LTimer timer;
    stringstream timeText;
    LTexture TimeTextTexture(renderer, gFont);
    SDL_Color textColor = { 0, 0, 0, 255 };

    bool ispause = false;
    SDL_Texture* preloading;
    int alpha = 255;

    SDL_Event e;


    remuse_b.image = SDL_CreateTextureFromSurface(renderer, i_resu);
    restart.image = SDL_CreateTextureFromSurface(renderer, i_restr);
    bkmn.image = SDL_CreateTextureFromSurface(renderer, i_qui);
    SDL_Texture* bgr = SDL_CreateTextureFromSurface(renderer, i_bgr);
    SDL_Texture* pau = SDL_CreateTextureFromSurface(renderer, i_pau);
    SDL_Texture* atext = SDL_CreateTextureFromSurface(renderer, i_red);
    p1.image = SDL_CreateTextureFromSurface(renderer, i_pla);

    for (int i = 0; i < 16; i++)
    {
        firstshot.blst[i].image = SDL_CreateTextureFromSurface(renderer, i_bul);
    }

    for (int i = 0; i < sizeof(rainlst) / sizeof(rainlst[0]); i++)
    {
        rainlst[i].x = rand()%(SCREEN_WIDTH - rainlst[i].w);
        rainlst[i].y = 0;
        rainlst[i].counter = rand()%100 + 50;
        rainlst[i].image = SDL_CreateTextureFromSurface(renderer, i_bul);
        rainlst[i].xdr = 0;
        rainlst[i].ydr = 5;
    }

    for (int i = 0; i < 8; i++)
    {
        horm[i].x = rand()%(SCREEN_WIDTH - horm[1].w);
        horm[i].y = 0;
        horm[i].fuel = rand()%900 - 200;
        if (horm[i].fuel < 200)
            horm[i].fuel = 200;
        horm[i].image = SDL_CreateTextureFromSurface(renderer, i_horm);
    }


    for (int i = 765; i >= 1; i -= 5)
    {
        switch (i)
        {
            case 765:
                preloading = SDL_CreateTextureFromSurface(renderer, i_resu);
                break;
            case 510:
                preloading = SDL_CreateTextureFromSurface(renderer, i_qui);
                break;
            case 255:
                preloading = SDL_CreateTextureFromSurface(renderer, i_restr);
                break;
        }
        alpha -= 5;
        SDL_SetTextureAlphaMod(preloading, alpha);
        SDL_RenderClear(renderer);

        rendersub(renderer, bgr, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        rendersub(renderer, preloading, SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 - 25, 100, 50);

        SDL_RenderPresent(renderer);
    }


    timer.start();
    while (isend == 1)
    {
        if (ispause)
        {
            SDL_RenderClear(renderer);

            rendersub(renderer, pau, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            if (e.type == SDL_MOUSEMOTION)
            {
                int pos_x = e.button.x + bkmn.x;
                int pos_y = e.button.y + bkmn.y;
                if (pos_x > remuse_b.x && pos_x < remuse_b.x + remuse_b.w && pos_y > remuse_b.y && pos_y < remuse_b.y + remuse_b.h)
                {
                    rendersub(renderer, atext, remuse_b.x-5, remuse_b.y-5, remuse_b.w+10, remuse_b.h+10);
                }

                if (pos_x > bkmn.x && pos_x < bkmn.x + bkmn.w && pos_y > bkmn.y && pos_y < bkmn.y + bkmn.h)
                {
                    rendersub(renderer, atext, bkmn.x-5, bkmn.y-5, bkmn.w+10, bkmn.h+10);
                }

                if (pos_x > restart.x && pos_x < restart.x + restart.w && pos_y > restart.y && pos_y < restart.y + restart.h)
                {
                    rendersub(renderer, atext, restart.x-5, restart.y-5, restart.w+10, restart.h+10);
                }
            }
            restart.render(renderer);
            remuse_b.render(renderer);
            bkmn.render(renderer);

            SDL_RenderPresent(renderer);

            SDL_WaitEventTimeout(&e, 10);

            if (e.type == SDL_QUIT)
            {
                quitSDL(window, renderer);
                break;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int pos_x = e.button.x + bkmn.x;
                int pos_y = e.button.y + bkmn.y;
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    if (pos_x > remuse_b.x && pos_x < remuse_b.x + remuse_b.w && pos_y > remuse_b.y && pos_y < remuse_b.y + remuse_b.h)
                    {
                        timer.unpause();
                        ispause = false;
                    }

                    else if (pos_x > bkmn.x && pos_x < bkmn.x + bkmn.w && pos_y > bkmn.y && pos_y < bkmn.y + bkmn.h)
                    {
                        isend = 0;
                        break;
                    }

                    else if (pos_x > restart.x && pos_x < restart.x + restart.w && pos_y > restart.y && pos_y < restart.y + restart.h)
                    {
                        isend = 1;
                        break;
                    }
                }
            }
        }
        else
        {
            timeText.str( "" );
            timeText << "score: " << ( timer.getTicks() ) ;
            TimeTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor );

            SDL_RenderClear(renderer);


            rendersub(renderer, bgr, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            TimeTextTexture.render( 0, 0);
            p1.render(renderer);

            for (int i = 0; i < sizeof(rainlst) / sizeof(rainlst[0]); i++)
            {
                if (rainlst[i].counter != 0)
                    rainlst[i].counter -= 1;
                else
                {
                    if (rainlst[i].inside(0,0,SCREEN_WIDTH,SCREEN_HEIGHT))
                    {
                        rainlst[i].render(renderer);
                    }
                    else
                    {
                        rainlst[i].x = rand()%(SCREEN_WIDTH - rainlst[i].w);
                        rainlst[i].y = 0;
                        rainlst[i].counter = rand()%200;
                        rainlst[i].xdr = 0;
                        rainlst[i].ydr = 5;
                        rainlst[i].render(renderer);
                    }
                    rainlst[i].move();
                }
            }
            if (timer.getTicks() > 3000)
            {
                if (firstshot.inside(0,0,SCREEN_WIDTH,SCREEN_HEIGHT))
                {
                    firstshot.render(renderer);
                    firstshot.type3_move();
                }
                else
                    firstshot.reset();
            }

            if (timer.getTicks() > 6000)
            {
                for (int i = 0; i < 8; i++)
                {
                    horm[i].render(renderer, p1);
                    horm[i].horming_move(p1);
                }
            }

            SDL_RenderPresent(renderer);

            SDL_WaitEventTimeout(&e, 10);

            if (e.type == SDL_QUIT)
                quitSDL(window, renderer);

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
            {
                timer.pause();
                ispause = true;
            }

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
                Bullet a = rainlst[i];
                Player p = p1;
                if ((a.x > p1.x && a.x < p1.x + p1.box_size && a.y + a.h > p.y && a.y + a.h < p.y + p.box_size) || (a.x + a.w > p1.x && a.x + a.w < p1.x + p1.box_size && a.y + a.h > p.y && a.y + a.h < p.y + p.box_size))
                {
                    isend = 2;
                    tscore = timer.getTicks();
                    timer.stop();
                }
            }
            for (int i = 0; i < 16; i++)
            {
                Bullet a = firstshot.blst[i];
                Player p = p1;
                if ((a.x > p1.x && a.x < p1.x + p1.box_size && a.y + a.h > p.y && a.y + a.h < p.y + p.box_size) || (a.x + a.w > p1.x && a.x + a.w < p1.x + p1.box_size && a.y + a.h > p.y && a.y + a.h < p.y + p.box_size))
                {
                    isend = 2;
                    tscore = timer.getTicks();
                    timer.stop();
                }
            }
            for (int i = 0; i < 8; i++)
            {
                Horming a = horm[i];
                Player p = p1;
                if ((a.x > p1.x && a.x < p1.x + p1.box_size && a.y + a.h > p.y && a.y + a.h < p.y + p.box_size) || (a.x + a.w > p1.x && a.x + a.w < p1.x + p1.box_size && a.y + a.h > p.y && a.y + a.h < p.y + p.box_size))
                {
                    isend = 2;
                    tscore = timer.getTicks();
                    timer.stop();
                }
            }
        }
    }
}