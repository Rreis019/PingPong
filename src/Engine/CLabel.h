#include "CControl.h"
#include <SDL2/SDL.h>
#include <string>

class CLabel : public CControl
{
public:
    CLabel(int x,int y,std::string fontName,SDL_Color color,int fontSize,char* str,...)
    {
        char buffer[100];
        va_list args;
        va_start(args,str);
        vsprintf(buffer,str,args);
        va_end(args);

        this->x = x;
        this->y = y;
        this->text = buffer;
        this->textColor = color;
        this->fontName = fontName;
        this->fontSize = fontSize;
    }

    void init();
    void draw();

    int getWidth(){return w;}
    int getHeight(){return h;}
    void setPos(int x,int y){this->x = x;this->y = y;}
    void setText(char* str,...);
    char* getText(){return (char*)text.c_str();}
    void setColor(SDL_Color color);
    void getRect(int& x,int& y,int& w,int& h){x = this->x;y = this->y;w = this->w;h = this->h;}
private:
    void createTexture(); //Render text to texture
    SDL_Texture* textTexture = nullptr;
    int w,h;
    std::string text;
    SDL_Color textColor;
    std::string fontName;
    int fontSize;
};

