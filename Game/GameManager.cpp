// GameManager.h                                                       
// Singleton                                                          
// Used to initialize and release                    
// Contains the game loop as well as the Update and Render functions   
// Used to make sure all functions are called in the correct order    
#include "GameManager.h"

GameManager* GameManager::sInstance = NULL;

GameManager* GameManager::Instance() {

	//Create a new instance if no instance was created before
	if (sInstance == NULL)
		sInstance = new GameManager();

	return sInstance;
}

void GameManager::Release() {

	delete sInstance;
	sInstance = NULL;
}

GameManager::GameManager() {

	mQuit = false;

	//Initialize SDL
	mGraphics = Graphics::Instance();

	// Quits the game if SDL fails to initialize
	if (!Graphics::Initialized())
		mQuit = true;


	//Initialize AssetManager
	mAssetMgr = AssetManager::Instance();

	//Initialize InputManager
	mInput = Input::Instance();

	//Initialize AudioManager
	mAudioMgr = AudioManager::Instance();

	//Initialize Timer
	mTimer = Timer::Instance();

	mScreenMgr = ScreenManager::Instance();
	
}

GameManager::~GameManager() {

	ScreenManager::Release();
	mScreenMgr = NULL;

	AudioManager::Release();
	mAudioMgr = NULL;

	AssetManager::Release();
	mAssetMgr = NULL;

	Graphics::Release();
	mGraphics = NULL;

	Input::Release();
	mInput = NULL;

	Timer::Release();
	mTimer = NULL;

}

void GameManager::EarlyUpdate() {

	//Updating the input state before any other updates are run to make sure the Input check is accurate
	mInput->Update();
}

void GameManager::Update() {

	mScreenMgr->Update();
	//GameEntity Updates should happen here
	/*
	mPlayScreen->Update();

	if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {

		mPlayScreen->StartNewGame();
	}*/

}

void GameManager::LateUpdate() {

	//Any collision detection should happen here

	mInput->UpdatePrevInput();
	mTimer->Reset();
}

void GameManager::Render() {

	//Clears the last frame's render from the back buffer
	mGraphics->ClearBackBuffer();

	//All other rendering is to happen here
	mScreenMgr->Render();

	//Renders the current frame
	mGraphics->Render();
}

void GameManager::Run() {

	while (!mQuit) {

		mTimer->Update();

		while (SDL_PollEvent(&mEvents) != 0) {
			//Checks if the user quit the game
			if (mEvents.type == SDL_QUIT) {

				mQuit = true;
			}
		}

		//Limits the frame rate to FRAME_RATE
		if (mTimer->DeltaTime() >= (1.0f / FRAME_RATE)) {

			EarlyUpdate();
			Update();
			LateUpdate();
			Render();
		}
	}
}
