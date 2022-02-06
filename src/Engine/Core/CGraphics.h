#include <SDL2/SDL.h>
#include "Vec2.h"
#include "RGBA.h"

//Classe responsavel por desenhar figuras geometricas
class CGraphics
{
public:
	CGraphics(){}
	CGraphics(SDL_Renderer* render) { renderer = render;}
	void DrawFilledRect(int x,int y,int w,int h,RGBA color);
	void DrawRect(int x,int y ,int w ,int h ,int thickness,RGBA color);
	void DrawLine(int x1,int y1,int x2,int y2,RGBA color);
	void DrawCircle(int32_t centreX, int32_t centreY, int32_t radius);
	void DrawFilledCircle(int x, int y, int radius,RGBA color);
	void DrawRotatedRect(int x,int y,int w,int h,float angle, RGBA color);
	void DrawVertices(Vec2* vertices, int verticeCount,  RGBA color);
	void DrawPoint(int x,int y, RGBA color);
private:
	//pointer SDL_RENDERER window
	SDL_Renderer* renderer = nullptr;
};

