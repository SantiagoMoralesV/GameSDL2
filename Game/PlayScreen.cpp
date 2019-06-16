#include "PlayScreen.h"



PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInput = Input::Instance();
	mAudio = AudioManager::Instance();

	mSideBar = new PlaySideBar();
	mSideBar->Parent(this);
	mSideBar->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.85f, Graphics::Instance()->SCREEN_HEIGHT*0.05f));
	mSideBar->SetLevel(3);

	mStartLabel = new Texture("START", "kenvector_future.ttf", 32, { 150, 0, 0 });
	mStartLabel->Parent(this);
	mStartLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.4f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	mLevel = NULL;
	mLevelStartDelay = 1.0f;
	mLevelStarted = false;
	
	mPlayer = NULL;
	mEnemy1 = NULL;
	Enemy::CreatePaths();
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

	mCurrentStage++;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;

	delete mLevel;
	mLevel = new Level(mCurrentStage, mSideBar, mPlayer, mEnemy1);
}

void PlayScreen::StartNewGame()
{
	delete mPlayer;
	
	mPlayer = new Player();// Creating new player
	mPlayer->Parent(this);
	mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.4f, Graphics::Instance()->SCREEN_HEIGHT*0.9f));
	mPlayer->Active(false);// Player is not active

	delete mEnemy1;

	mEnemy1 = new Enemy1();// Creating new Enemy
	mEnemy1->Parent(this);
	mEnemy1->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.4f, Graphics::Instance()->SCREEN_HEIGHT*0.1f));
	mEnemy1->Active(false);// Enemy is not active


	mSideBar->SetHighScore(30000);
	mSideBar->SetShips(mPlayer->Lives());
	mSideBar->SetPlayerScore(mPlayer->Score());
	mSideBar->SetLevel(0);

	mGameStarted = false;
	mLevelStarted = false;
	mLevelStartTimer = 0.0f;

	mCurrentStage = 0;

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

		if (!mLevelStarted) {

			mLevelStartTimer += mTimer->DeltaTime();
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
			mSideBar->Update();

		if (mLevelStarted) {

			mLevel->Update();

			//check if level is finished or not 
			if (mLevel->State() == Level::finished) {

				mLevelStarted = false;
			}
		}

		mPlayer->Update();
		mEnemy1->Update();
	}
}

void PlayScreen::Render()
{

	mSideBar->Render();

	// if Game has not started render label 'Start'
	if (!mGameStarted) 
		mStartLabel->Render();
	
	if (mGameStarted && mLevelStarted) 

		if(mLevelStarted)
			mLevel->Render();

	mPlayer->Render();
	mEnemy1->Render();

}
