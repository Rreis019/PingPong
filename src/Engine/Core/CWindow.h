#include "CSingleton.h"
#include "CGraphics.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>

class CWindow : public CSingleton<CWindow>
{
public:
	//Width and height of the window
	int width, height;

	//Init window
	bool Init();
	
	//
	void Free();

	void Render();
	
	void Events();
	
	void GameLoop();

    SDL_Renderer* renderer;
	CGraphics* getGraphics(){return &graphics;}
private:
	CGraphics graphics;
    SDL_Window* window;
    bool isRunning = true;
};



