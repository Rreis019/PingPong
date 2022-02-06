#include "CClock.h"

void CClock::CalcFps()
{
	Uint32 elapsedMS = SDL_GetTicks() - StartTime;
	double elapsedSeconds = elapsedMS / 1000.0; // Convert to seconds
	this->Framerate = FpsCount / elapsedSeconds; // FPS is Frames / Seconds
}

void CClock::ITick(int LimitFps)
{
	FpsCount++;
	Uint32 EndTick = SDL_GetTicks();

	//da skip primeiro frame
	if (StartTick == 0)
	{
		StartTick = EndTick;
		return;
	}

	Dt = EndTick - StartTick;
	//Limit the fps
	if ((1000 / LimitFps) > Dt)
		SDL_Delay(1000 / LimitFps - (Dt));

	CalcFps();
	StartTick = SDL_GetTicks();

	TimeScale = 60.0f / (float)this->Framerate;
}
