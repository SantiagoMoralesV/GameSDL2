#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H
#include "Animation.h"
#include "Input.h"
#include "Scoreboard.h"

class StartScreen : public GameObject
{
public:
	StartScreen();
	~StartScreen();
	void Update();
	void Render();


	//for current mode in game
	int SelectedMode();
	void ChangeSelectedMode(int change);

private:

	Input* mInput;
	//screen entities
	//topBar entities
	GameObject* mTopbar;
	Texture* mPlayer;
	Texture* mHiScore;
	Scoreboard* mPlayerScore;
	Scoreboard* mTopScore;

	//Logo entities
	Texture* mLogo;

	//Play mode entities
	GameObject* mPlayModes;
	Texture* mStartGame;
	Texture* mInstructions;
	Texture* mQuit;
	Texture* mCursor;
	Vector2 mCursorStartPos;
	Vector2 mCursorOffSet;
	int mSelectedMode;
};

#endif
