#include "PlayScreen.h"



PlayScreen::PlayScreen()
{
	// Timer instance
	mTimer = Timer::Instance();
	// Input Instance
	mInput = Input::Instance();
	// Audio Instance
	mAudio = AudioManager::Instance();

	mSideBar = new PlaySideBar();//creating side bar
	mSideBar->Parent(this);// relative to its parent 
	// Position of the side bar right side of the screen
	mSideBar->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.85f, Graphics::Instance()->SCREEN_HEIGHT*0.05f));
	
	// new texture of label Start, size and color
	mStartLabel = new Texture("START", "kenvector_future.ttf", 32, { 150, 0, 0 });
	//relative to its parent 
	mStartLabel->Parent(this);
	//position of the start label on the screen
	mStartLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.4f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	mLevel = NULL;
	// delay for the level start
	mLevelStartDelay = 1.0f;
	mLevelStarted = false;
	
	mPlayer = NULL;
	mEnemy1 = NULL;

}


PlayScreen::~PlayScreen()
{
	mTimer = NULL;
	mInput = NULL;

	delete mSideBar;
	mSideBar = NULL;

	delete mStartLabel;
	mStartLabel = NULL;

	delete mLevel;
	mLevel = NULL;

	delete mPlayer;
	mPlayer = NULL;

	delete mEnemy1;
	mEnemy1 = NULL;
}

void PlayScreen::StartNextLevel() {
	// increase stage by 1
	mCurrentStage++;
	//timer starts at 0
	mLevelStartTimer = 0.0f;
	// sets level started to true 
	mLevelStarted = true;

	// if there is a level delete it 
	delete mLevel;
	// create a new level  with a current stage, 
	mLevel = new Level(mCurrentStage, mSideBar, mPlayer, mEnemy1);
}

void PlayScreen::StartNewGame()
{
	//if there was a player before delete it
	delete mPlayer;
	
	mPlayer = new Player();// Creating new player
	// relative to its parent
	mPlayer->Parent(this);
	//Player position on the screen once is active
	mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.4f, Graphics::Instance()->SCREEN_HEIGHT*0.9f));
	mPlayer->Active(false);// Player starts at the beginning as not active

	// if there was an enemy before delete it
	delete mEnemy1;

	mEnemy1 = new Enemy1();// Creating new Enemy
	mEnemy1->Parent(this);// relative to its parent
	// Position of the enemy on the screen
	mEnemy1->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.4f, Graphics::Instance()->SCREEN_HEIGHT*0.1f));
	mEnemy1->Active(false);// Enemy is not active at the start of the game

	// setting score on side bar of 30000
	mSideBar->SetHighScore(30000);
	// setting lives of the player in side bar(2 ships)
	mSideBar->SetShips(mPlayer->Lives());
	// setting player score in side bar
	mSideBar->SetPlayerScore(mPlayer->Score());
	// Begins the game at level 0
	mSideBar->SetLevel(0);

	// Game starts as false (displays labels first)
	mGameStarted = false;
	// level started set as false at the beginning of the game
	mLevelStarted = false;
	// set up timer at 0 secs
	mLevelStartTimer = 0.0f;

	// begins with a current stage of 0
	mCurrentStage = 0;
	// plays music intro while the start label is on
	mAudio->PlayMusic("musicIntro.wav", 0);
	
}

bool PlayScreen::GameOver()
{
	// if level hasnt started yet return false
	if (!mLevelStarted) {
		return false;
	}
	// if level state is GameOver return true
	return (mLevel->State() == Level::gameover);
}

void PlayScreen::Update()
{
	// remove the Start label from the middle of the screen once the music stops playing
	if (mGameStarted) {
		// if level has not started we want to increase the start timer
		if (!mLevelStarted) {

			mLevelStartTimer += mTimer->DeltaTime();
			// once it equals level start delay start next level
			if (mLevelStartTimer >= mLevelStartDelay) {
				StartNextLevel();
			}
		}

	} else {
		// if music is not playing Start Game
		if (!Mix_PlayingMusic()) {

			mGameStarted = true;
		}
	}

	if (mGameStarted) {
	
		if(mCurrentStage > 0)
			// update play side bar if current stage is greater than 0
			mSideBar->Update();

		if (mLevelStarted) {

			mLevel->Update();

			//check if level is finished or not 
			if (mLevel->State() == Level::finished) {

				mLevelStarted = false;
			}
		}
		// if player is active able to handle movement and firing
		// if not handle animation
		mPlayer->Update();
		// if player is active moving from right to left and left to right
		// if not renders death animation
		mEnemy1->Update();
	}
}

void PlayScreen::Render()
{
	// we want to always render the side bar while on the Playscreen
	mSideBar->Render();

	// if Game has not started render label 'Start'
	// only displayed once after pressing RETURN in the menu 
	if (!mGameStarted) 
		mStartLabel->Render();
	
	if (mGameStarted && mLevelStarted) 

		if(mLevelStarted)
			mLevel->Render();// renders stage label, stage number and ready label in sequence

	mPlayer->Render();//Renders player after labels have finished
	mEnemy1->Render();//Renders enemy after labels have finished

}
