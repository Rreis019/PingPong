#include "CLabel.h"
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>
#include  "CWindow.h"

void CLabel::init(){createTexture();}
void CLabel::draw()
{
    if(text.length() == 0)
        return;

    SDL_Rect rect = {x, y, w, h};
    SDL_RenderCopy(CWindow::Get().renderer, textTexture, NULL, &rect);
}


void CLabel::setText(char* str,...)
{
    char buffer[100];
    va_list args;
    va_start(args,str);
    vsprintf(buffer,str,args);
    va_end(args);

    this->text = buffer;
    createTexture();
}

void CLabel::setColor(SDL_Color color)
{
    this->textColor = color;
    createTexture();
}

void CLabel::createTexture(){

    if(textTexture != nullptr)
    {
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }

    if(text.length() == 0)
        return;

    CWindow& window =  CWindow::Get();
    TTF_Font* font = TTF_OpenFont((const char*)fontName.c_str(), fontSize);
    SDL_Surface* textSurface = TTF_RenderText_Solid(font,text.c_str(), textColor);
    textTexture = SDL_CreateTextureFromSurface(CWindow::Get().renderer, textSurface);
    SDL_QueryTexture(textTexture, NULL, NULL, &w, &h);

    SDL_FreeSurface(textSurface);      
    TTF_CloseFont(font);
}

