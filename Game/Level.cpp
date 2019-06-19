#include "Level.h"

Level::Level(int stage, PlaySideBar* sideBar, Player* player, Enemy1* enemy)
{ 
	mTimer = Timer::Instance();
	mSidebar = sideBar;
	// sets the stage
	mSidebar->SetLevel(stage);

	mStage = stage;
	mStageStarted = false;

	mLabelTimer = 0.0f;
	// creates the stage label, size and color
	mStageLabel = new Texture("STAGE", "kenvector_future.ttf", 32, { 75, 75, 200 });
	// relative to its parent
	mStageLabel->Parent(this);
	// position of stage label in the screen
	mStageLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.4f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	// creating stage number
	mStageNumber = new Scoreboard({ 75, 75, 200 });
	// sets the stage to the score
	mStageNumber->Score(mStage);
	//relative to its parent
	mStageNumber->Parent(this);
	//position of the stage number (next to the stage label)
	mStageNumber->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	mStageLabelOnScreen = 0.0f;
	mStageLabelOffScreen = 1.5f;

	// creating Ready label, size and color
	mReadyLabel = new Texture("Ready", "kenvector_future.ttf", 32, { 150, 0, 0 });
	//relative to its parent
	mReadyLabel->Parent(this);
	// position of the ready label (same as the stage label)
	mReadyLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.4f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	mReadyLabelOnScreen = mStageLabelOffScreen;
	mReadyLabelOffScreen = mReadyLabelOnScreen + 3.0f;

	mPlayer = player;
	mPlayerHit = false;// starts as false
	mPlayerRespawnDelay = 0.009f;// wait half second to respawns the player (after animation explosion is done)
	mPlayerRespawnTimer = 0.0f;// the timer counting starts at 0.0f
	mPlayerRespawnLabelOnScreen = 2.0f;// the timer is counting once it hits 2 shows the ready label

	mEnemy1 = enemy;

	// new label for the Game Over
	mGameOverLabel = new Texture("GAME OVER", "kenvector_future.ttf", 32, { 150, 0, 0 });
	mGameOverLabel->Parent(this);
	// Same position as the Ready Label
	mGameOverLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.4f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

	mGameOver = false;// starts at false
	mGameOverDelay = 6.0f;// wait for 6 seconds before we move on to start screen or another screen
	mGameOverTimer = 0.0f;// timer starts counting at 0.0f
	mGameOverLabelOnScreeen = 1.0f; // wait for one second before showing the Game Over label 

	mCurrentState = running;

	
}
Level::~Level()
{
	mTimer = NULL;
	mSidebar = NULL;

	delete mStageLabel;
	mStageLabel = NULL;

	delete mStageNumber;
	mStageNumber = NULL;

	delete mReadyLabel;
	mReadyLabel = NULL;

	mPlayer = NULL;
	mEnemy1 = NULL;

	delete mGameOverLabel;
	mGameOverLabel = NULL;

}

void Level::StartStage()
{
	mStageStarted = true;
}

void Level::HandleStartLabels()
{
	mLabelTimer += mTimer->DeltaTime();
	if (mLabelTimer >= mStageLabelOffScreen) {

		if (mStage > 1) {

			StartStage();
		}
		else {

			if (mLabelTimer >= mReadyLabelOffScreen) {

				StartStage();
				mPlayer->Active(true);
				mPlayer->Visible(true);
				mEnemy1->Active(true);
				mEnemy1->Visible(true);
			
			}
		}
	}
}

void Level::HandleCollisions()
{
	if (!mPlayerHit) {

		if (Input::Instance()->KeyPressed(SDL_SCANCODE_X)) {

			mPlayer->WasHit();// the player was hit
			mSidebar->SetShips(mPlayer->Lives());// update lives on the side bar

			mPlayerHit = true;
			mPlayerRespawnTimer = 0.0f;// reset timer to 0.0f
			mPlayer->Active(false);// player cant move around 
		}
	}
}

void Level::HandlePlayerDeath()
{
	// once the animation has done been playing
	if (!mPlayer->IsAnimating()) {

		// check for player lives
		if (mPlayer->Lives() > 0) {

			if (mPlayerRespawnTimer == 0.0f) {
				//after player explosion is done make the player dissapear to show label
				mPlayer->Visible(false);

			// start increasing the Respawn timer
			mPlayerRespawnTimer += mTimer->DeltaTime();
			// set Player back to normal on the screen
			if (mPlayerRespawnTimer >= mPlayerRespawnDelay) {

				mPlayer->Active(true);
				mPlayer->Visible(true);
				mPlayerHit = false;
				}
			}
		}
		else {

			if (mGameOverTimer == 0.0f)
				mPlayer->Visible(false);

			mGameOverTimer += mTimer->DeltaTime();
			if (mGameOverTimer >= mGameOverDelay) {

				mCurrentState = gameover;
			}
		}
	}
}

Level::LEVEL_STATES Level::State() {

	return mCurrentState;
}

void Level::Update()
{
	if(!mStageStarted) {
		// handle labels
		HandleStartLabels();

	} else {
		//mEnemy->Update();

		// where we handle all collisions
		HandleCollisions();

		// if player has been hit handle the player dead
		if (mPlayerHit) {

			HandlePlayerDeath();

		} else {
			// otherwise finish the level
			if (Input::Instance()->KeyPressed(SDL_SCANCODE_N)) {

				mCurrentState = finished;

			}
		}
	}
}

void Level::Render()
{
	if (!mStageStarted) {

		if (mLabelTimer > mStageLabelOnScreen && mLabelTimer < mStageLabelOffScreen) {

			mStageLabel->Render();
			mStageNumber->Render();
		}
		else if (mLabelTimer > mReadyLabelOnScreen && mLabelTimer < mReadyLabelOffScreen) {

			mReadyLabel->Render();
		}
	}
	else {
		//mEnemy->Render();

		// if player was hit
		if (mPlayerHit) {
			// Renders the Ready label on the screen once player is ready again
			if (mPlayerRespawnTimer >= mPlayerRespawnLabelOnScreen)
				mReadyLabel->Render();

			if (mGameOverTimer >= mGameOverLabelOnScreeen)
				mGameOverLabel->Render();

		}
	}
}
