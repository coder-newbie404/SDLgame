#include <iostream>
#include <cstring>
#include <sstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_vulkan.h>
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
SDL_Surface* i_3 = IMG_Load("res/3.png");
SDL_Surface* i_2 = IMG_Load("res/2.png");
SDL_Surface* i_1 = IMG_Load("res/1.png");
SDL_Surface* i_paused = IMG_Load("res/paused.png");
SDL_Surface* i_type3 = IMG_Load("res/type3.png");


void gamerunning(SDL_Window* window, SDL_Renderer* renderer, int &isend, int &tscore)
{
    TTF_Font* gFont = TTF_OpenFont( "res/BlackOpsOne-Regular.ttf", 28 );
    Mix_Music *gMusic = Mix_LoadMUS( "res/gunsound.wav" );


    const Uint8 *state = SDL_GetKeyboardState(NULL);
    Button remuse_b(SCREEN_WIDTH - 200, 370, 150, 60);
    Button restart(SCREEN_WIDTH - 200, 500, 150, 60);
    Button bkmn(SCREEN_WIDTH - 200, 630, 150, 60);
    Player p1(700, SCREEN_HEIGHT, SCREEN_WIDTH);
    Bullet rainlst[rand()%60 + 15];
    Type3 firstshot(rand()%(SCREEN_WIDTH - firstshot.blst[0].w), rand()%(SCREEN_HEIGHT - firstshot.blst[0].h));
    Type3 secondshot(rand()%(SCREEN_WIDTH - secondshot.blst[0].w), rand()%(SCREEN_HEIGHT - secondshot.blst[0].h));
    Type3 thirdshot(rand()%(SCREEN_WIDTH - thirdshot.blst[0].w), rand()%(SCREEN_HEIGHT - thirdshot.blst[0].h));
    Horming horm[8];

    LTimer timer;
    stringstream timeText;
    LTexture TimeTextTexture(renderer, gFont);
    SDL_Color textColor = {53, 49, 133, 255};

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
    SDL_Texture* paused = SDL_CreateTextureFromSurface(renderer, i_paused);
    p1.image = SDL_CreateTextureFromSurface(renderer, i_pla);

    for (int i = 0; i < 16; i++)
    {
        firstshot.blst[i].image = SDL_CreateTextureFromSurface(renderer, i_type3);
        secondshot.blst[i].image = SDL_CreateTextureFromSurface(renderer, i_type3);
        thirdshot.blst[i].image = SDL_CreateTextureFromSurface(renderer, i_type3);
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
                preloading = SDL_CreateTextureFromSurface(renderer, i_3);
                break;
            case 510:
                preloading = SDL_CreateTextureFromSurface(renderer, i_2);
                break;
            case 255:
                preloading = SDL_CreateTextureFromSurface(renderer, i_1);
                break;
        }
        alpha -= 5;
        SDL_SetTextureAlphaMod(preloading, alpha);
        SDL_RenderClear(renderer);

        rendersub(renderer, bgr, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        rendersub(renderer, preloading, SCREEN_WIDTH/2 - 36, SCREEN_HEIGHT/2 - 50, 72, 100);
        p1.render(renderer);

        SDL_RenderPresent(renderer);
        SDL_WaitEventTimeout(&e, 10);
        if (e.type == SDL_QUIT)
                quitSDL(window, renderer);
    }


    timer.start();
    if(Mix_PlayMusic(gMusic, -1)==-1)
        printf("Mix_PlayMusic: %s\n", Mix_GetError());
    while (isend == 1)
    {
        if (ispause)
        {
            SDL_RenderClear(renderer);

            rendersub(renderer, pau, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            rendersub(renderer, paused, 50, 50, 406, 106);
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
                        Mix_ResumeMusic();
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
            if (timer.getTicks() > 12000)
            {
                if (firstshot.inside(0,0,SCREEN_WIDTH,SCREEN_HEIGHT))
                {
                    firstshot.render(renderer);
                    firstshot.type3_move();
                }
                else
                    firstshot.reset();
            }
            if (timer.getTicks() > 20000)
            {
                if (secondshot.inside(0,0,SCREEN_WIDTH,SCREEN_HEIGHT))
                {
                    secondshot.render(renderer);
                    secondshot.type3_move();
                }
                else
                    secondshot.reset();
            }
            if (timer.getTicks() > 30000)
            {
                if (thirdshot.inside(0,0,SCREEN_WIDTH,SCREEN_HEIGHT))
                {
                    thirdshot.render(renderer);
                    thirdshot.type3_move();
                }
                else
                    thirdshot.reset();
            }

            if (timer.getTicks() > 45000)
            {
                for (int i = 0; i < 8; i++)
                {
                    horm[i].render(renderer, p1);
                    horm[i].horming_move(p1);
                }
            }

            SDL_RenderPresent(renderer);

            SDL_PollEvent(&e);

            if (e.type == SDL_QUIT)
                quitSDL(window, renderer);

            if (state[SDL_SCANCODE_ESCAPE])
            {
                timer.pause();
                Mix_PauseMusic();
                ispause = true;
            }
            if (state[SDL_SCANCODE_UP])
                p1.move(1);
            if (state[SDL_SCANCODE_RIGHT])
                p1.move(2);
            if (state[SDL_SCANCODE_DOWN])
                p1.move(3);
            if (state[SDL_SCANCODE_LEFT])
                p1.move(4);

            bool endgame = false;
            for (int i = 0; i < sizeof(rainlst) / sizeof(rainlst[0]); i++)
            {
                Bullet a = rainlst[i];
                if (a.dead(p1))
                {
                    endgame = true;
                }
            }

            if (firstshot.dead(p1) || secondshot.dead(p1) || thirdshot.dead(p1))
            {
                endgame = true;
            }

            for (int i = 0; i < 8; i++)
            {
                if (horm[i].dead(p1))
                {
                    endgame = true;
                }
            }

            if (endgame)
            {
                Mix_HaltMusic();
                isend = 2;
                tscore = timer.getTicks();
                timer.stop();
            }
        }
    }
}
