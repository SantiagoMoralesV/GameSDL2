#include "ScreenManager.h"

ScreenManager * ScreenManager::sInstance = NULL;

ScreenManager::ScreenManager()
{
	//initialising all values
	mInput = Input::Instance();
	mStartScreen = new StartScreen();
	mCurrentScreen = start;
}


ScreenManager::~ScreenManager()
{
	mInput = NULL;
	delete mStartScreen;
	mStartScreen = NULL;
}

ScreenManager * ScreenManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new ScreenManager();
	}
	return sInstance;
}

void ScreenManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

void ScreenManager::Update()
{
	switch (mCurrentScreen)
	{
	case start:
		mStartScreen->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_RETURN))
		{
			mCurrentScreen = play;
		}
		break;
	case play:
		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE))
		{
			mCurrentScreen = start;
		}
		break;
	default:
		break;
	}
}

void ScreenManager::Render()
{
	switch (mCurrentScreen)
	{
	case start:
		mStartScreen->Render();

		break;
	case play:
		break;
	default:
		break;
	}
}
