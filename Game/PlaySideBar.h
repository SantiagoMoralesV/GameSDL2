#ifndef _PLAYSIDEBAR_H
#define _PLAYSIDEBAR_H
#include "Timer.h"
#include "Scoreboard.h"
#include "AudioManager.h"

class PlaySideBar : public GameObject 
{
private:
	// used for the labels
	Timer* mTimer;
	// creates the background of the side bar (black)
	Texture* mBackground;
	// creates High label
	Texture* mHighLabel;
	// creates Score label
	Texture* mScoreLabel;
	// creates the high score number
	Scoreboard* mHighScoreboard;
	//creates 1UP label
	Texture* mPlayerLabel;
	//creates the player score 
	Scoreboard* mPlayerScore;

	// displays a maximum of 3 ship  textures (lives of the player)
	static const int MAX_SHIP_TEXTURES = 3;
	
	// new object of the player ship
	GameObject* mShips;
	// creates the ships (lives) textures
	Texture* mShipTextures[MAX_SHIP_TEXTURES];
	// displays a number of the total ships(in case player has more lives)
	Scoreboard* mTotalShipsLabel;
	// holds the number of total ships to be displayed as a texture and number
	int mTotalShips;
	// holds the remaining levels
	int mRemainingLevels;
	// used as a timer
	float mFlagTimer;
	// used for a flag interval
	float mFlagInterval;

public:

	PlaySideBar();
	~PlaySideBar();

	// used to set the highscore
	void SetHighScore(int score);
	// used to set player score
	void SetPlayerScore(int score);
	// used to set the ships of the player (lives)
	void SetShips(int ships);
	// set the level the player starts
	void SetLevel(int level);

	void Update();
	void Render();
};

#endif // !_PLAYSIDEBAR_H