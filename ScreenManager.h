#ifndef _SCREENMANAGER_H_
#define _SCREENMANAGER_H_
#include "StartScreen.h"

class ScreenManager
{
public:
	ScreenManager();
	~ScreenManager();

	static ScreenManager* Instance();
	static void Release();

	void Update();
	void Render();

private:
	//for switching screens
	enum SCREENS{start,play};

	static ScreenManager* sInstance;
	//to get input to start or play 
	Input* mInput;

	StartScreen* mStartScreen;

	SCREENS mCurrentScreen;
};

#endif