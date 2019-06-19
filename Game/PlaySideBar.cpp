#include "PlaySideBar.h"



PlaySideBar::PlaySideBar()
{

	mTimer = Timer::Instance();
	// texture of the background on side bar
	mBackground = new Texture("black.png");
	//relative to its parent
	mBackground->Parent(this);
	// position on the screen
	mBackground->Pos(Vector2(60.0f, 380.0f));
	// scale the background
	mBackground->Scale(Vector2(3.0f, 10.0f));

	// new texture High Label, size and color
	mHighLabel = new Texture("High", "kenvector_future.ttf", 32, { 150, 0, 0 });
	// relative to its parent
	mHighLabel->Parent(this);
	// position on the side bar
	mHighLabel->Pos(Vector2(-20.0, 0.0f));

	// new texture Score, size and color
	mScoreLabel = new Texture("Score", "kenvector_future.ttf", 32, { 150, 0, 0 });
	// relative to its parent
	mScoreLabel->Parent(this);
	//position of the score label in side bar
	mScoreLabel->Pos(Vector2(40.0f, 25.0f));

	// creating a scoreboard number
	mHighScoreboard = new Scoreboard();
	// relative to its parent
	mHighScoreboard->Parent(this);
	// position of the high score in the side bar
	mHighScoreboard->Pos(Vector2(85.0f, 50.0f));

	// create a new texture 1up, size and color
	mPlayerLabel = new Texture("1UP", "kenvector_future.ttf", 32, { 150, 0, 0 });
	//relative to its parent
	mPlayerLabel->Parent(this);
	//position in the side bar
	mPlayerLabel->Pos(Vector2(-30.0f, 160.0f));

	// create a new player score
	mPlayerScore = new Scoreboard();
	// relative to parent
	mPlayerScore->Parent(this);
	// position of the player score in the side bar
	mPlayerScore->Pos(Vector2(90.0f, 192.0f));

	// create a new game object
	mShips = new GameObject();
	//relative to its parent
	mShips->Parent(this);
	// position  in the side bar
	mShips->Pos(Vector2(-15.0f, 300.0f));

	// loop throught the maximum ship textures
	for (int i = 0; i < MAX_SHIP_TEXTURES; i++) {

		// create the texture of the ship
		mShipTextures[i] = new Texture("player2.png");
		mShipTextures[i]->Parent(mShips);
		// position of the ships 
		// display up to the max ships, takes the width and height and displays it evenly 
		mShipTextures[i]->Pos(Vector2(86.0f * (i % 2), 70.0f * (i / 2)));
	}
	// create a new scoreboard
	mTotalShipsLabel = new Scoreboard();
	// relative to its parent
	mTotalShipsLabel->Parent(mShips);
	// displays the total ship in a number if the player has more that 3 lives
	mTotalShipsLabel->Pos(Vector2(105.0f, 75.0f));

	mFlagTimer = 0.0f;
	mFlagInterval = 0.5f;
	
}


PlaySideBar::~PlaySideBar()
{
	mTimer = NULL;

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
	// set high scores
	mHighScoreboard->Score(score);
}

void PlaySideBar::SetPlayerScore(int score)
{
	// sets player score
	mPlayerScore->Score(score);
}

void PlaySideBar::SetShips(int ships)
{
	// set the ships (lives)
	mTotalShips = ships;

	if (ships > MAX_SHIP_TEXTURES) {
		mTotalShipsLabel->Score(ships);
	}
}

void PlaySideBar::SetLevel(int level)
{
	// sets levels
	mRemainingLevels = level;

}

void PlaySideBar::Update()
{
	// updates flag timer depending on the levels
	if (mRemainingLevels > 0){

		mFlagTimer += mTimer->DeltaTime();
		if (mFlagTimer >= mFlagInterval) {

			mFlagTimer = 0.0f;
		}
	}

}

void PlaySideBar::Render()
{

	// renders the black background
	mBackground->Render();
	// renders the High label
	mHighLabel->Render();
	// renders the Score label
	mScoreLabel->Render();
	// renders the number belos the high score label
	mHighScoreboard->Render();
	// renders the 1UP label
	mPlayerLabel->Render();
	// renders the player label score 
	mPlayerScore->Render();
	mShips->Render();

	for (int i = 0; i < MAX_SHIP_TEXTURES && i < mTotalShips; i++) {
		// renders the ships textures
		mShipTextures[i]->Render();
	}

	if (mTotalShips > MAX_SHIP_TEXTURES) {
		// renders number of total ships
		mTotalShipsLabel->Render();
	}

	
}
