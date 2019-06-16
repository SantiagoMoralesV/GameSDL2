#ifndef _PLAYSCREEN_H
#define _PLAYSCREEN_H
#include "Level.h"


class PlayScreen : public GameObject
{

private:
	Timer* mTimer;
	Input* mInput;
	AudioManager* mAudio;

	PlaySideBar* mSideBar;
	Player* mPlayer;
	Enemy1* mEnemy1;
	Texture* mStartLabel;

	float mLevelStartTimer;
	float mLevelStartDelay;

	bool mGameStarted;

	Level* mLevel;
	bool mLevelStarted;
	int mCurrentStage;
	
	// Load next level after the one just finished
	void StartNextLevel();

public:
	PlayScreen();
	~PlayScreen();

	// Function called From ScreenManager to start a new game
	void StartNewGame();

	bool GameOver();

	void Update();

	void Render();
};

#endif // !_PLAYSCREEN_H