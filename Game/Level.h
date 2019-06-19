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
	// used for the labels
	Timer* mTimer;
	// Used to set levels in sidebar
	PlaySideBar* mSidebar;

	int mStage;// holds the stage the player is currently on
	bool mStageStarted;//true if game has started

	float mLabelTimer;// timer for the label

	Texture* mStageLabel;// create stage label
	Scoreboard* mStageNumber;// create stage number
	float mStageLabelOnScreen;// used to display the stage label on the screen
	float mStageLabelOffScreen;// used to remove label on screen

	Texture* mReadyLabel;// create Ready label
	float mReadyLabelOnScreen;// used to display ready label on the screen
	float mReadyLabelOffScreen;// used to remove ready label on the screen

	Player* mPlayer;// create the Player
	bool mPlayerHit;// true when the player is hit by a bullet
	float mPlayerRespawnDelay;// the time the player waits after it has been hit after player explosion
	float mPlayerRespawnTimer;// increments and waits for the delay
	float mPlayerRespawnLabelOnScreen;// Shows the ready label before player has respawed

	Texture* mGameOverLabel;// Texture for the Game Over Label
	bool mGameOver;// it will be set to true if player runs out of lives
	float mGameOverDelay;// the time for the waits after player run out of lives
	float mGameOverTimer;// increments and waits for the delay
	float mGameOverLabelOnScreeen;// The GameOver label can be shown if player run out of lives

	// Keeps track of the states;
	LEVEL_STATES mCurrentState;

	//Enemy* mEnemy;
	Enemy1* mEnemy1;

	void StartStage();// returns if the stage has started
	void HandleStartLabels();// show labels Stage, Ready
	void HandleCollisions();// Handles collisions
	void HandlePlayerDeath();// Handles player death

public:
	// called by the playerScreen taking the stage, sidebar, player and enemy
	Level(int stage, PlaySideBar* sideBar, Player* player, Enemy1* enemy1);

	~Level();

	// returns the state of the level
	LEVEL_STATES State();

	//Updates labels on the screen, handles collision, and player death animation and new level
	void Update();
	
	// renders labels and player death animation
	void Render();

};

#endif 
