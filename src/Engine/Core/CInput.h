#pragma once
#include "CSingleton.h"
#include <SDL2/SDL.h>
#include "../Vec2.h"

class CInput : public CSingleton<CInput>
{
public:
	void onUpdate(SDL_Event& event);
	static bool isKeyDown(int index) { return Get().KeysDown[index]; }
	static bool isKeyPressed(int index) { return Get().KeysPressed[index]; }
	static bool isLeftButtonDown() { return Get().IisLeftButtonDown(); }
	static bool isRightButtonDown() { CInput::Get().IisRightButtonDown(); }
	static Vec2 getMousePos() { return Vec2(Get().MouseX, Get().MouseY); }
	static bool LeftMouseClicked() { return Get().ILeftMouseClicked(); }
	static bool RightMouseClicked() { return Get().IRightMouseClicked(); }

	bool IisKeyDown(int index) { return KeysDown[index]; }
	bool IiKeyPressed(int index) { return KeysPressed[index]; }
	bool IisLeftButtonDown() { return LeftButtonDown; }
	bool IisRightButtonDown() { return RightButtonDown; }
	Vec2 IgetMousePos() { return Vec2(MouseX, MouseY); }
	bool ILeftMouseClicked() { return LeftButtonUp; }
	bool IRightMouseClicked() { return RightButtonUp; }
	void Reset() { 
		LeftButtonUp = false;
		RightButtonUp = false;
		memset(KeysPressed, 0, sizeof(KeysPressed)); 
		}
private:
	//Internal functions
	#define MAX_KEYS 256
	bool KeysDown[MAX_KEYS];
	bool KeysPressed[MAX_KEYS];

	bool LeftButtonDown = false;
	bool RightButtonDown = false;
	bool LeftButtonUp = false, RightButtonUp = false;
	int MouseX = 0, MouseY = 0;
};