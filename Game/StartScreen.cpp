#include "StartScreen.h"



StartScreen::StartScreen()
{
	mInput = Input::Instance();

	//screen entities
	mTopbar = new GameObject(Graphics::Instance()->SCREEN_WIDTH * 0.5f, 80.0f);
	mPlayer = new Texture("Player", "ArcadeClassic.ttf", 32, { 200, 0, 0 });
	mHiScore = new Texture("HI SCORE", "ArcadeClassic.ttf", 32, { 200, 0, 0 });
	mPlayerScore = new ScoreBoard();
	mTopScore = new ScoreBoard();

	//keeping elements in TopBar
	mPlayer->Parent(mTopbar);
	mHiScore->Parent(mTopbar);
	mPlayerScore->Parent(mTopbar);
	mTopScore->Parent(mTopbar);

	//setting position of the topBar elements
	mPlayer->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH*0.25f, 0.0f));
	mHiScore->Pos(Vector2(120.0f,0.0f));

	mPlayerScore->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH*0.23f, 30.0f));
	mTopScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.21f, 30.0f));

	mTopScore->Score(5000);

	mTopbar->Parent(this);

	//Logo entities
	mLogo = new Texture("logo.png", 0, 0, 318, 163);
	
	mLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.4f));
	mLogo->Parent(this);


	//Play Mode entities
	//setting up options for player
	mPlayModes = new GameObject(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.65f);
	mStartGame = new Texture("Start Game", "ArcadeClassic.ttf", 32, {230, 230, 230});
	mInstructions = new Texture("Help", "ArcadeClassic.ttf", 32, { 230, 230, 230 });
	mQuit = new Texture("Quit", "ArcadeClassic.ttf", 32, { 230, 230, 230 });
	mCursor = new Texture("cursor.png");
	
	mStartGame->Parent(mPlayModes);
	mInstructions->Parent(mPlayModes);
	mQuit->Parent(mPlayModes);
	mCursor->Parent(mPlayModes);

	mStartGame->Pos(Vector2(-40.0f,-30.0f));
	mInstructions->Pos(Vector2(-40.0f, 5.0f));
	mQuit->Pos(Vector2(-40.0f, 40.0f));
	mCursor->Pos(Vector2(-150.0f, -30.0f));
	
	mPlayModes->Parent(this);

	mCursorStartPos = mCursor->Pos(local);
	mCursorOffSet = Vector2(0.0f, 35.0f);
}


StartScreen::~StartScreen()
{
	//freeing TopBar entities
	delete mTopbar; // releases Topbar instance
	mTopbar = NULL;// sets Topbar to Null
	delete mPlayer;// releases Player instance
	mPlayer = NULL;// sets mPlayer to Null
	delete mHiScore;// releases HiScore instance
	mHiScore = NULL;// sets mHiScore to Null
	delete mPlayerScore;
	mPlayerScore = NULL;
	delete mTopScore;
	mTopScore = NULL;

	//deleting logo entities
	delete mLogo;
	mLogo = NULL;

	//deleting Play mode entities
	delete mPlayModes;
	mPlayModes = NULL;
	delete mStartGame;
	mStartGame = NULL;
	delete mInstructions;
	mInstructions = NULL;
	delete mQuit;
	mQuit = NULL;
	delete mCursor;
	mCursor = NULL;

}

void StartScreen::Update()
{
	if (mInput->KeyPressed(SDL_SCANCODE_DOWN))
	{
		ChangeSelectedMode(1);
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_UP))
	{
		ChangeSelectedMode(-1);
	}
}

void StartScreen::Render()
{
	mPlayer->Render();
	mHiScore->Render();
	mPlayerScore->Render();
	mTopScore->Render();
	
	mLogo->Render();

	mStartGame->Render();
	mInstructions->Render();
	mQuit->Render();
	mCursor->Render();
}

int StartScreen::SelectedMode()
{
	return mSelectedMode;
}

void StartScreen::ChangeSelectedMode(int change)
{
	mSelectedMode += change;
	for (int i = 0; i <= 2; i++)
	{
		if (mSelectedMode < 0)
		{
			mSelectedMode++;
		}
		else if (mSelectedMode > 2)
		{
			mSelectedMode--;
		}
	}
	
	mCursor->Pos(mCursorStartPos + mCursorOffSet * mSelectedMode);
}