#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H
#include "Graphics.h"
#include "Timer.h"
#include "GameObject.h"

class GameManager
{
public:
	
	// it returns instance
	static GameManager* Instance();
	// clear any static memory allocation
	static void Release();
	// loop keeps game running
	void Run();


private:

	GameManager();
	~GameManager();

	// initiliaze instance
	static GameManager* sInstance;

	// variable for the frame rate
	const int  FRAME_RATE = 60;


	bool mQuit;
	// Graphics pointer which will call mGraphics
	Graphics* mGraphics;
	// variable pointing Timer
	Timer* mTimer;
	// catch the events of the user
	SDL_Event mEvents;

	GameObject* mParent;
	GameObject* mChild;


};

#endif 