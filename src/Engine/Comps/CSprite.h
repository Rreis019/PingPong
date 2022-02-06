#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "CComponent.h"
#include "RGBA.h"
class CSprite : public CComponent
{
public:
	int witdh = 0,height = 0;
	std::string filepath = "";
	int flip = SDL_FLIP_NONE;//SDL_RendererFlip
	RGBA transparent = {0,0,0,0};

	CSprite() {}
	CSprite(const char * filename);
	CSprite(const char * filename, unsigned char TransparentR, unsigned char TransparentG, unsigned char TransparentB);
	void onStart();
	void onRender();
	void setSize(int w, int h);
	void serialise(FILE* fp);
	void deserialise(FILE* fp);
	~CSprite();
private:
	
	SDL_Texture* image_texture = nullptr;
};