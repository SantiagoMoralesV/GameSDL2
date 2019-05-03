#include "Timer.h"

Timer* Timer::sInstance = NULL;

Timer * Timer::Instance()
{
	// if instance was not created before
	if (sInstance == NULL) 
		// create new instance
		sInstance = new Timer();
	
	// return instance
	return sInstance;
}
void Timer::Release()
{
	// delete instance and set it to NULL
	delete sInstance;
	sInstance = NULL;
	
}

void Timer::Reset()
{
	// number of milliseconds since the library initialize
	mStartTicks = SDL_GetTicks();
	// set elapsed ticks to zero
	mElapsedTicks = 0;
	// set DeltaTime to 0
	mDeltaTime = 0.0f;
}

float Timer::DeltaTime()
{
	// returns DeltaTime
	return mDeltaTime;
}

void Timer::TimeScale(float t)
{
	mTimeScale = t;
}

float Timer::TimeScale()
{
	//returns Time scale
	return mTimeScale;
}

void Timer::Update()
{
	// the ticks that happened between the last reset and the current time
	mElapsedTicks = SDL_GetTicks() - mStartTicks;
	// since Ticks are in milliseconds converted back to float
	mDeltaTime = mElapsedTicks * 0.001f;
}

Timer::Timer()
{
	Reset();
	mTimeScale = 1.0f;
}


Timer::~Timer()
{
}




