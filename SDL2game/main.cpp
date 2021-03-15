#include <iostream>
#include <SDL.h>
#include <cstring>

using namespace std;

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Tiny Game!";

struct Player
{
    int x = 100;
    int y = 10;
    int xdr = 5;
    int ydr = 0;
    int box_size = 5;
    int dir = 1;
    void render(SDL_Renderer* renderer)
    {
        SDL_Rect filled_rect;
        filled_rect.x=x;
        filled_rect.y=y;
        filled_rect.w=box_size;
        filled_rect.h=box_size;
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &filled_rect);
    }

    void move()
    {
        x+=xdr;
        y+=ydr;
    }

    void move_left()
    {
        xdr = -2;
        ydr = 0;
        move();
    }
    void move_right()
    {
        xdr = 2;
        ydr = 0;
        move();
    }
    void move_up()
    {
        xdr = 0;
        ydr = -2;
        move();
    }
    void move_down()
    {
        xdr = 0;
        ydr = 2;
        move();
    }

    bool inside(int minx, int miny, int maxx, int maxy)
    {
        return (minx<=x && miny<=y && maxx>=x+box_size && maxy>=y+box_size);
    }
};

struct Rain
{
    int x;
    int y = 5;
    int xdr = 0;
    int ydr = rand()%6+5;
    int box_size = 10;
    void render(SDL_Renderer* renderer)
    {
        SDL_Rect filled_rect;
        filled_rect.x=x;
        filled_rect.y=y;
        filled_rect.w=box_size;
        filled_rect.h=box_size;
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(renderer, &filled_rect);
    }

    void move()
    {
        x+=xdr;
        y+=ydr;
    }
    bool inside(int minx, int miny, int maxx, int maxy)
    {
        return (minx<=x && miny<=y && maxx>=x+box_size && maxy>=y+box_size);
    }
};

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       //SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    //Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    Player p1;
    Rain rainlst[rand()%5+1];

    for (int i = 0; i < sizeof(rainlst) / sizeof(rainlst[0]); i++)
    {
        rainlst[i].x = rand()%796+5;
    }

    SDL_Event e;
    while(true){

        int x_direct = 5;
        int y_direct = 5;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        int count = 0;
        for (int i = 0; i < sizeof(rainlst) / sizeof(rainlst[0]); i++)
        {
            if (rainlst[i].inside(0,0,SCREEN_WIDTH,SCREEN_HEIGHT) == false);
                count += 1;
        }
        if (count == sizeof(rainlst) / sizeof(rainlst[0]))
        {
            Rain rainlst[rand()%5+1];

            for (int i = 0; i < sizeof(rainlst) / sizeof(rainlst[0]); i++)
            {
            rainlst[i].x = rand()%796+5;
            }
        }



        p1.render(renderer);
        for (int i = 0; i < sizeof(rainlst) / sizeof(rainlst[0]); i++)
        {
            rainlst[i].render(renderer);
        }

        SDL_RenderPresent(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(10);

        if (p1.inside(0,0,SCREEN_WIDTH,SCREEN_HEIGHT) == false)
        {
            p1.xdr = 0;
            p1.ydr = 0;
        }

        for (int i = 0; i < sizeof(rainlst) / sizeof(rainlst[0]); i++)
        {
            rainlst[i].move();
        }
        p1.move();

        if (SDL_WaitEventTimeout(&e,10))
        {
            for (int i = 0; i < sizeof(rainlst) / sizeof(rainlst[0]); i++)
            {
                rainlst[i].move();
            }
            switch (p1.dir)
            {
                case 1:
                    p1.move_left();
                    break;
                case 2:
                    p1.move_right();
                    break;
                case 3:
                    p1.move_down();
                    break;
                case 4:
                    p1.move_up();
                    break;
                default: break;
            }
        }

        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN)
        {
        	switch (e.key.keysym.sym)
        	{
        		case SDLK_ESCAPE: quitSDL(window, renderer); break;
        		case SDLK_LEFT:
        			p1.dir = 1;
        			break;
            	case SDLK_RIGHT:
            	    p1.dir = 2;
            		break;
            	case SDLK_DOWN:
            	    p1.dir = 3;
					break;
            	case SDLK_UP:
            	    p1.dir = 4;
            		break;
        		default: break;
			}
        }

    }
    //waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
