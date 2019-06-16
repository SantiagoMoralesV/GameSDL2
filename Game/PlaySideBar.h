#ifndef _PLAYSIDEBAR_H
#define _PLAYSIDEBAR_H
#include "Timer.h"
#include "Scoreboard.h"
#include "AudioManager.h"

class PlaySideBar : public GameObject 
{
private:

	Timer* mTimer;
	AudioManager* mAudio;

	Texture* mBackground;

	Texture* mHighLabel;
	Texture* mScoreLabel;
	Scoreboard* mHighScoreboard;

	Texture* mPlayerLabel;
	Scoreboard* mPlayerScore;

	static const int MAX_SHIP_TEXTURES = 3;
	GameObject* mShips;
	Texture* mShipTextures[MAX_SHIP_TEXTURES];
	Scoreboard* mTotalShipsLabel;
	int mTotalShips;

	int mRemainingLevels;
	float mFlagTimer;
	float mFlagInterval;

public:

	PlaySideBar();
	~PlaySideBar();

	void SetHighScore(int score);
	void SetPlayerScore(int score);
	void SetShips(int ships);
	void SetLevel(int level);

	void Update();
	void Render();
};

#endif // !_PLAYSIDEBAR_H