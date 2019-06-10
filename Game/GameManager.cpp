// GameManager.h                                                       
// Singleton                                                          
// Used to initialize and release                    
// Contains the game loop as well as the Update and Render functions   
// Used to make sure all functions are called in the correct order    
#include "GameManager.h"

//Initializing to NULL
GameManager* GameManager::sInstance = NULL;

GameManager * GameManager::Instance()
{
	//Create a new instance if no instance was created before
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
	mQuit = false;

	//Initialize SDL
	mGraphics = Graphics::Instance();

	if (!Graphics::Initialized()) {
		// exit game loop and exit program
		mQuit = true;
	}

	mAssetMgr = AssetManager::Instance();//Initialize AssetManager
	mInput = Input::Instance();//Initialize Input
	mAudioMgr = AudioManager::Instance();

	mTimer = Timer::Instance();//Initialize Timer

	mTex = new Texture("Hello World", "kenvector_future.ttf", 25, { 200, 0, 0 });
	mTex->Pos(Vector2(400, 200));

	mPlayer = new Player();// Creating new player
	mPlayer->Pos(Vector2(400, 550));// Position of the player
	mPlayer->Active(true);// Player is active
	mPlayer->Visible(true);// Player is visible
	mPlayerHit = false;// PlayerHit set to false

	mEnemy = new Enemy();// Creating new enemy
	mEnemy->Pos(Vector2(400, 50)); // Position of the player
	mEnemy->Active(true);// Enemy is Active
	mEnemy->Visible(true);// Enemy is Visible
	mEnemyHit = false; // EnemyHit set to false
}


GameManager::~GameManager()
{
	AudioManager::Release();
	mAudioMgr = NULL;
	
	AssetManager::Release();// releases AssetManager instance
	mAssetMgr = NULL;// sets AssetManager to NULL
	
	Graphics::Release();// releases Graphics instance
	mGraphics = NULL;// sets Graphics to NULL
	
	Input::Release();// releases Input instance
	mInput = NULL;// sets mInput to NULL

	Timer::Release();// releases Timer instance
	mTimer = NULL;// sets mInput to NULL

	delete mPlayer;// releases Player instance
	mPlayer = NULL;// sets mPlayer to Null

	delete mEnemy;// releases Player instance
	mEnemy = NULL;// sets mPlayer to Null
}

void GameManager::EarlyUpdate() {
	//Updating the input state before any other updates are run to make sure the Input check is accurate
	mInput->Update();
}

void GameManager::Update() {

	//GameObject Updates happen here
	if (Input::Instance()->KeyPressed(SDL_SCANCODE_X)) {
		
		mPlayer->WasHit();
		mPlayerHit = true;
		mPlayer->Active(false);
		mAudioMgr->PlaySFX("sfx_laser1.ogg");// plays only once
		mAudioMgr->PlayMusic("Audio.mp3");//continues playing music
	}
	else {

		mInput->Update();
		mPlayer->Update();
		mPlayer->Active(true);
		mEnemy->Update();
		mEnemy->Active(true);
	}
}

void GameManager::LateUpdate()
{
	mInput->UpdatePrevInput();
	mTimer->Reset();
}

void GameManager::Render()
{
	//Clears the last frame's render from the back buffer
	mGraphics->ClearBackBuffer();

	mTex->Render();
	// Render Player
	mPlayer->Render();
	// Renders Enemy
	mEnemy->Render();
	//Renders the current frame
	mGraphics->Render();
}

void GameManager::Run()
{
	while (!mQuit) {
		//Update timer at the beginning of each iteration
		mTimer->Update();

		while (SDL_PollEvent(&mEvents) != 0) {
			//Checks if the user quit the game
			if (mEvents.type == SDL_QUIT) {

				mQuit = true;
			}
		}
		//Limits the frame rate to FRAME_RATE
		if (mTimer->DeltaTime() >= 1.0f / FRAME_RATE) {

			EarlyUpdate();
			Update();
			LateUpdate();
			Render();

		}
	}
}
