#ifndef _SCREENMANAGER_H_
#define _SCREENMANAGER_H_
#include "StartScreen.h"
#include "PlayScreen.h"

class ScreenManager
{

public:

	static ScreenManager* Instance();
	static void Release();

	void Update();
	void Render();

private:

	ScreenManager();
	~ScreenManager();
	//for switching screens
	enum SCREENS{ start, play };

	static ScreenManager* sInstance;
	//to get input to start or play 
	Input* mInput;

	StartScreen* mStartScreen;
	Scoreboard* mTopScore;
	PlayScreen* mPlayScreen;
	SCREENS mCurrentScreen;
};

#endif
