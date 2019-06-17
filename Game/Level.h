#ifndef _LEVEL_H
#define _LEVEL_H
#include "PlaySideBar.h"
#include "Player.h"
#include "Enemy1.h"

class Level : public GameObject
{
public:

	//add enum to keep track of the state of the level, if level is running, finished or game over
	enum LEVEL_STATES { running, finished, gameover };

private:

	Timer* mTimer;
	PlaySideBar* mSidebar;

	int mStage;
	bool mStageStarted;

	float mLabelTimer;

	Texture* mStageLabel;
	Scoreboard* mStageNumber;
	float mStageLabelOnScreen;
	float mStageLabelOffScreen;

	Texture* mReadyLabel;
	float mReadyLabelOnScreen;
	float mReadyLabelOffScreen;

	Player* mPlayer;
	bool mPlayerHit;// true when the player is hit by a bullet
	float mPlayerRespawnDelay;// the time the player waits after it has been hit after player explosion
	float mPlayerRespawnTimer;// increments and waits for the delay
	float mPlayerRespawnLabelOnScreen;// Shows the ready label before player has respawed

	bool mEnemyHit;

	Texture* mGameOverLabel;// Texture for the Game Over Label
	bool mGameOver;// it will be set to true if player runs out of lives
	float mGameOverDelay;// the time for the waits after player run out of lives
	float mGameOverTimer;// increments and waits for the delay
	float mGameOverLabelOnScreeen;// The GameOver label can be shown if player run out of lives

	// Keeps track of the states;
	LEVEL_STATES mCurrentState;

	//Enemy* mEnemy;
	Enemy1* mEnemy1;

	void StartStage();
	void HandleStartLabels();// show labels Stage, Ready
	void HandleCollisions();// Handles collisions
	void HandlePlayerDeath();// Handles player death

	void HandleEnemyDeath();
public:

	Level(int stage, PlaySideBar* sideBar, Player* player, Enemy1* enemy1);

	~Level();

	// returns the state of the level
	LEVEL_STATES State();

	void Update();

	void Render();

};

#endif 
