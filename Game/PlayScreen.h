#ifndef _PLAYSCREEN_H
#define _PLAYSCREEN_H
#include "Level.h"


class PlayScreen : public GameObject
{

private:
	// used for start a game
	Timer* mTimer;
	// used for input in the play screen
	Input* mInput;
	// used for audio in the play screen (start label audio)
	AudioManager* mAudio;

	//used for the side bar in the play screen
	PlaySideBar* mSideBar;
	// used for the player in the play screen
	Player* mPlayer;
	//used for the enemy in the play screen
	Enemy1* mEnemy1;
	// used for the start label 
	Texture* mStartLabel;

	float mLevelStartTimer;
	float mLevelStartDelay;

	bool mGameStarted;// if is true the game has started if not handle labels

	// used to create a new Level(mCurrentStage, mSideBar, mPlayer, mEnemy1);
	Level* mLevel;
	bool mLevelStarted;// updates the level once is true if not the level has not started
	int mCurrentStage;// the stage the player is on currently and increases by one
	
	// Load next level after the one just finished
	void StartNextLevel();

public:
	PlayScreen();
	~PlayScreen();

	// Function called From ScreenManager to start a new game
	void StartNewGame();

	bool GameOver();// true if the game is over, false if player still playing 

	void Update();// updates music and if the game has started

	void Render();// keeps rendering the side bar (labels, player and enemy depending if game has started)
};

#endif // !_PLAYSCREEN_H