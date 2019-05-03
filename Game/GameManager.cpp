#include "GameManager.h"


GameManager* GameManager::sInstance = NULL;

GameManager * GameManager::Instance()
{
	// if instance was not created before
	if (sInstance == NULL) 
		// create new instance
		sInstance = new GameManager();
	
	// return instance
	return sInstance;
}

void GameManager::Release()
{
	// delete instance and set it to NULL
	delete sInstance;
	sInstance = NULL;
	
}


GameManager::GameManager()
{
	// start mQuit as false
	mQuit = false;
	// Initialize our graphics
	mGraphics = Graphics::Instance();

	if (!Graphics::Initialized()) {
		// exit game loop and exit program
		mQuit = true;
	}

	mTimer = Timer::Instance();
}


GameManager::~GameManager()
{
	// releases singleton instance
	Graphics::Release();
	// sets Graphics to NULL
	mGraphics = NULL;

	Timer::Release();
	mTimer = NULL;
}

void GameManager::Run()
{
	while (!mQuit) {
		//Update timer at the beginning of each iteration
		mTimer->Update();

		while (SDL_PollEvent(&mEvents) != 0) {

			if (mEvents.type == SDL_QUIT) {

				mQuit = true;
			}
		}
		if (mTimer->DeltaTime() >= 1.0f / FRAME_RATE) {
		
			std::cout << "DeltaTime:" << mTimer->DeltaTime() << std::endl;

			mGraphics->Render();

			mTimer->Reset();
		}
	}
}
