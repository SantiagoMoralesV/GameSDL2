#include "PlaySideBar.h"



PlaySideBar::PlaySideBar()
{

	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mBackground = new Texture("black.png");
	mBackground->Parent(this);
	mBackground->Pos(Vector2(60.0f, 380.0f));
	mBackground->Scale(Vector2(3.0f, 10.0f));

	mHighLabel = new Texture("High", "kenvector_future.ttf", 32, { 150, 0, 0 });
	mHighLabel->Parent(this);
	mHighLabel->Pos(Vector2(-20.0, 0.0f));

	mScoreLabel = new Texture("Score", "kenvector_future.ttf", 32, { 150, 0, 0 });
	mScoreLabel->Parent(this);
	mScoreLabel->Pos(Vector2(40.0f, 25.0f));

	mHighScoreboard = new Scoreboard();
	mHighScoreboard->Parent(this);
	mHighScoreboard->Pos(Vector2(85.0f, 50.0f));

	mPlayerLabel = new Texture("1UP", "kenvector_future.ttf", 32, { 150, 0, 0 });
	mPlayerLabel->Parent(this);
	mPlayerLabel->Pos(Vector2(-30.0f, 160.0f));

	mPlayerScore = new Scoreboard();
	mPlayerScore->Parent(this);
	mPlayerScore->Pos(Vector2(90.0f, 192.0f));

	mShips = new GameObject();
	mShips->Parent(this);
	mShips->Pos(Vector2(-15.0f, 300.0f));

	for (int i = 0; i < MAX_SHIP_TEXTURES; i++) {

		mShipTextures[i] = new Texture("player2.png");
		mShipTextures[i]->Parent(mShips);
		mShipTextures[i]->Pos(Vector2(86.0f * (i % 2), 70.0f * (i / 2)));
	}

	mTotalShipsLabel = new Scoreboard();
	mTotalShipsLabel->Parent(mShips);
	mTotalShipsLabel->Pos(Vector2(105.0f, 75.0f));

	mFlagTimer = 0.0f;
	mFlagInterval = 0.5f;
	
}


PlaySideBar::~PlaySideBar()
{
	mTimer = NULL;
	mAudio = NULL;

	delete mBackground;
	mBackground = NULL;

	delete mHighLabel;
	mHighLabel = NULL;

	delete mScoreLabel;
	mScoreLabel = NULL;

	delete mHighScoreboard;
	mHighScoreboard = NULL;

	delete mPlayerLabel;
	mPlayerLabel = NULL;

	delete mPlayerScore;
	mPlayerScore = NULL;

	delete mShips;
	mShips = NULL;

	for (int i = 0; i < MAX_SHIP_TEXTURES; i++) {

		delete mShipTextures[i];
		mShipTextures[i] = NULL;
	}

	delete mTotalShipsLabel;
	mTotalShipsLabel = NULL;
}

void PlaySideBar::SetHighScore(int score)
{
	mHighScoreboard->Score(score);
}

void PlaySideBar::SetPlayerScore(int score)
{
	mPlayerScore->Score(score);
}

void PlaySideBar::SetShips(int ships)
{
	mTotalShips = ships;

	if (ships > MAX_SHIP_TEXTURES) {
		mTotalShipsLabel->Score(ships);
	}
}

void PlaySideBar::SetLevel(int level)
{
	mRemainingLevels = level;

}

void PlaySideBar::Update()
{
	if (mRemainingLevels > 0){

		mFlagTimer += mTimer->DeltaTime();
		if (mFlagTimer >= mFlagInterval) {

			mFlagTimer = 0.0f;
		}
	}

}

void PlaySideBar::Render()
{

	mBackground->Render();

	mHighLabel->Render();
	mScoreLabel->Render();
	mHighScoreboard->Render();
	mPlayerLabel->Render();
	mPlayerScore->Render();
	mShips->Render();

	for (int i = 0; i < MAX_SHIP_TEXTURES && i < mTotalShips; i++) {
		
		mShipTextures[i]->Render();
	}

	if (mTotalShips > MAX_SHIP_TEXTURES) {
		mTotalShipsLabel->Render();
	}

	
}
