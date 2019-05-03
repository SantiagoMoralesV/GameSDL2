#ifndef _TIMER_H
#define _TIMER_H

#include <SDL.h>

class Timer
{
public:
	

	// it returns instance
	static Timer* Instance();
	// clears any static memory allocation
	static void Release();

	void Reset();
	float DeltaTime();

	void TimeScale(float t);
	float TimeScale();

	void Update();

private:

	Timer();
	~Timer();

	static Timer* sInstance;

	unsigned int mStartTicks;
	unsigned int mElapsedTicks;
	float mDeltaTime;
	float mTimeScale;

};

#endif
