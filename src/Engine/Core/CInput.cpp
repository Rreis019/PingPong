#include "CInput.h"
#include <stdio.h>

//Events
void CInput::onUpdate(SDL_Event& event)
{
	switch (event.type)
    {	
		case SDL_KEYDOWN:
    	 	if(event.key.keysym.scancode < MAX_KEYS)
    	 	{
				KeysDown[event.key.keysym.scancode] = true;
    	 	}
            break;
		case SDL_KEYUP:
    	 	if(event.key.keysym.scancode < MAX_KEYS)
    	 	{
				KeysDown[event.key.keysym.scancode] = false;
				KeysPressed[event.key.keysym.scancode] = true;
    	 	}
        	break;
		case SDL_MOUSEBUTTONDOWN:
			if(event.button.button == SDL_BUTTON_LEFT)
				LeftButtonDown = true;
			else if(event.button.button == SDL_BUTTON_RIGHT)
				RightButtonDown = true;
			break;
		case SDL_MOUSEBUTTONUP:
			if(event.button.button == SDL_BUTTON_LEFT)
			{
				LeftButtonDown = false;
				LeftButtonUp = true;
			}
			else if(event.button.button == SDL_BUTTON_RIGHT)
			{
				RightButtonDown = false;
				RightButtonUp = true;
			}
			break;
		case SDL_MOUSEMOTION:
			MouseX = event.motion.x;
			MouseY = event.motion.y;
			break;


    }
}
