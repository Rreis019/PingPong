#pragma once
#include <SDL2/SDL.h>
#include "CSingleton.h"
//Responsavel por limitar os fps e conseguir fps do jogo
class CClock : public CSingleton<CClock>
{
public:
	static void Tick(int LimitFps){
		return Get().ITick(LimitFps);
	}
	//Return framerate
	static int GetFps() { return Get().Framerate; }

	//Delta time between the frames in MS
	float Dt = 0;

	//Multiply speed * timescale
	float TimeScale = 1.0f;

	//When started the mainloop
	float StartTime = 0;
private:
	Uint32 StartTick = 0;
	int Framerate = 0;
	int FpsCount = 0;

	//Update clock and Limit fps
	void ITick(int LimitFps);
	void CalcFps();
};
