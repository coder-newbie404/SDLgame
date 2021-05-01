#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <sstream>
#include "general_helper.h"
#include "g_name_input.h"
#include "Ltexture.h"
#include "o_button.h"

using namespace std;
SDL_Surface* ibgr = IMG_Load("res/inputname.png");
SDL_Surface* istart = IMG_Load("res/start.png");
SDL_Surface* ired = IMG_Load("res/a.png");

void inputname(SDL_Window* window, SDL_Renderer* renderer, string &name)
{
    TTF_Font* Font = TTF_OpenFont( "res/BlackOpsOne-Regular.ttf", 32 );

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    Button startButton(50, SCREEN_HEIGHT - 100, 500, 60);
    LTexture InputTextTexture(renderer, Font);
    SDL_Color textColor = {53, 49, 133, 255};

    SDL_Texture* sbgr = SDL_CreateTextureFromSurface(renderer, ibgr);
    SDL_Texture* Abgr = SDL_CreateTextureFromSurface(renderer, ired);
    startButton.image = SDL_CreateTextureFromSurface(renderer, istart);

    string inputText = " ";
    InputTextTexture.loadFromRenderedText( inputText.c_str(), textColor );

    SDL_StartTextInput();

    SDL_Event e;

    while(true)
    {
        bool quit = false;
        //The rerender text flag
        bool renderText = false;

        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quitSDL(window, renderer);
            }
            if (state[SDL_SCANCODE_RETURN])
            {
                if (inputText == " ")
                    name = "NoName";
                else
                    name = inputText;
                quit = true;
            }
            //Special key input
            else if( e.type == SDL_KEYDOWN )
            {
                //Handle backspace
                if( e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
                {
                    //lop off character
                    inputText.pop_back();
                    renderText = true;
                }
                //Handle copy
                else if( e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
                {
                    SDL_SetClipboardText( inputText.c_str() );
                }
                //Handle paste
                else if( e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
                {
                    inputText = SDL_GetClipboardText();
                    renderText = true;
                }
            }
            //Special text input event
            else if( e.type == SDL_TEXTINPUT )
            {
                //Not copy or pasting
                if( !( SDL_GetModState() & KMOD_CTRL && ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' || e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) ) )
                {
                    if (inputText.length() < 20)
                    //Append character
                    inputText += e.text.text;
                    renderText = true;
                }
            }
        }

        //Rerender text if needed
        if( renderText )
        {
            //Text is not empty
            if( inputText != "" )
            {
                //Render new text
                InputTextTexture.loadFromRenderedText( inputText.c_str(), textColor );
            }
            //Text is empty
            else
            {
                //Render space texture
                InputTextTexture.loadFromRenderedText( " ", textColor );
            }
        }

        SDL_RenderClear( renderer );
        rendersub(renderer, sbgr, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

        //Render text textures
        InputTextTexture.render(800, 180);

        startButton.render(renderer);

        //Update screen
        SDL_RenderPresent( renderer );
        if (quit)
            break;
    }

    SDL_StopTextInput();
}
