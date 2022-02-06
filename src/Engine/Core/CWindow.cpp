#include "CWindow.h"
#include "CClock.h"
#include "CInput.h"


#define GAME_TITLE "PING PONGOOOOO"
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

bool CWindow::Init()
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    //Init Tff
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    //Create window
    window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,  SDL_WINDOW_SHOWN);
    width = SCREEN_WIDTH; height = SCREEN_HEIGHT;
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    //Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    //set window to 1024x800 size
    



    graphics = CGraphics(renderer);

    return true;
}

void CWindow::Free()
{
	//free window
    SDL_DestroyWindow(window);
    //free renderer
    SDL_DestroyRenderer(renderer);

    //Quit SDL subsystems
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void CWindow::GameLoop()
{
    while (isRunning)
    {
        CClock::Tick(60);
        Events();
        Render();
    }
}
