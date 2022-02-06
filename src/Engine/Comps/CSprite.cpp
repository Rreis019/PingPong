#include "CSprite.h"
#include  "CWindow.h"
#include "CGameObject.h"
#include "CEntityManager.h"
#include "CCamera.h"
#include "CScene.h"
#include "CComponentFactory.h"
#include "Serialization.h"

REGISTER_COMPONENT(CSprite);

CSprite::CSprite(const char * filename)
{
	this->name = (char*)"CSprite";
	this->filepath = filename;
}

CSprite::CSprite(const char * filename, unsigned char TransparentR, unsigned char TransparentG, unsigned char TransparentB)
{
	this->name = "CSprite";
	filepath = filename;
	transparent.r = TransparentR;
	transparent.g = TransparentG;
	transparent.b = TransparentB;
	transparent.a = 255;
}

void CSprite::onStart()
{
	this->name = "CSprite";
	if(filepath == ""){return;}
	SDL_Surface*  image_surface = IMG_Load(filepath.c_str());
	witdh = image_surface->w;
	height = image_surface->h;

	if((int)transparent.a != 0)
		SDL_SetColorKey(image_surface, SDL_TRUE, SDL_MapRGB(image_surface->format, transparent.r, transparent.g, transparent.b));

	image_texture = SDL_CreateTextureFromSurface(CWindow::Get().renderer, image_surface);
	SDL_FreeSurface(image_surface);	
}


void CSprite::onRender()
{
	CCamera* cam = CEntityManager::Get().getCurrentCamera();
	Vec2 size; size.x = witdh * owner->scale.x; size.y = height * owner->scale.y;
	Vec2 out = owner->getPos();
	
	if(cam != nullptr)
	{
		if(!cam->WorldToScreen(owner->getPos(),size, out))
			return;
	}	

	SDL_Rect rect = 
	{
		 (int)out.x, 
		 (int)out.y,
		 (float)size.x,
		 (float)size.y 		 
	};
	SDL_RenderCopyEx(CWindow::Get().renderer, image_texture, NULL, &rect, owner->angle, NULL, (SDL_RendererFlip)flip);
}

CSprite::~CSprite()
{
	//printf("Sprite Destructor\n");
	SDL_DestroyTexture(image_texture);

}

void CSprite::setSize(int w, int h)
{
	//set size image_texture
	witdh = w;
	height = h;
}

void CSprite::serialise(FILE* fp)
{
	SAVE(fp,witdh);
	SAVE(fp,height);
	SAVE(fp,filepath);
	SAVE(fp,flip);
	SAVE(fp,transparent.r);
	SAVE(fp,transparent.g);
	SAVE(fp,transparent.b);
	SAVE(fp,transparent.a);
}

void CSprite::deserialise(FILE* fp)
{
	READ(fp,witdh);
	READ(fp,height);
	READ(fp,filepath);
	READ(fp,flip);
	READ(fp,transparent.r);
	READ(fp,transparent.g);
	READ(fp,transparent.b);
	READ(fp,transparent.a);
}