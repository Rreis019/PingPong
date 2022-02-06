#include "CGraphics.h"
void CGraphics::DrawFilledRect(int x,int y,int w,int h, RGBA color)
{
 	SDL_Rect rect = {x,y,w,h};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void CGraphics::DrawRect(int x,int y ,int w ,int h ,int thickness,RGBA color)
{
	DrawFilledRect(x - thickness,y,thickness,h,color); //  Left border -> |
	DrawFilledRect(x + w,y,thickness,h,color); //  Right border -> |
	DrawFilledRect(x-thickness,y- thickness ,w + thickness*2,thickness,color); //  Top border -> -
	DrawFilledRect(x-thickness,y+h,w + thickness*2,thickness,color); //  Bottom border -> -
} 

void CGraphics::DrawLine(int x1,int y1,int x2,int y2,RGBA color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

//https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
void CGraphics::DrawCircle(int32_t centreX, int32_t centreY, int32_t radius)
{
   const int32_t diameter = (radius * 2);

   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}


void CGraphics::DrawFilledCircle(int x, int y, int radius,RGBA color)
{
    SDL_SetRenderDrawColor(renderer, color.r,color.g,color.b,color.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}


void CGraphics::DrawRotatedRect(int x,int y,int w,int h,float angle,RGBA color)
{
    Vec2 center  = Vec2(x+(w/2),y+(h/2));
    Vec2 vertices[4] = 
    { 
        Vec2(x,y), //left top
        Vec2(x+w,y),//right top
        Vec2(x,y+h),//left bottom
        Vec2(x+w,y+h)//right bottom
    };

    for(int i = 0;i < 4;i++){vertices[i] = Vec2::rotate(center,vertices[i],angle);}

    DrawLine(vertices[0].x,vertices[0].y,vertices[1].x,vertices[1].y,color);//--- top
    DrawLine(vertices[0].x,vertices[0].y,vertices[2].x,vertices[2].y,color);// | left
    DrawLine(vertices[1].x,vertices[1].y,vertices[3].x,vertices[3].y,color);// | right
    DrawLine(vertices[2].x,vertices[2].y,vertices[3].x,vertices[3].y,color);//--- bottom
}


void CGraphics::DrawPoint(int x,int y,RGBA color)
{
    SDL_SetRenderDrawColor(renderer, color.r,color.g,color.b,color.a);
    SDL_RenderDrawPoint(renderer, x, y);
}

void CGraphics::DrawVertices(Vec2* vertices, int verticeCount, RGBA color)
{
    for(int i = 0;i < verticeCount;i++){DrawFilledRect(vertices[i].x-1,vertices[i].y-1,2,2,color);}
}