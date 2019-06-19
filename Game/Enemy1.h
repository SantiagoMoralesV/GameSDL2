#ifndef _ENEMY1_H
#define _ENEMY1_h
#include "Animation.h"
#include "Input.h"
#include "Bullet.h"
#include "AudioManager.h"


class Enemy1 : public PhysEntity
{

private:
	//Used to get the deltatime to handle movement on the player
	Timer* mTimer;
	//Used to get the input on the player
	Input* mInput;
	AudioManager* mAudio;

	bool mVisible;// if true show player ship
	bool mAnimating;// if true show death player animation

	Texture* mEnemy1;// create a texture for player

	Animation* mDeathAnimation;// create a death animation for player

	float mMoveSpeed;// set speed for texture
	Vector2 mMoveBounds;// set bounds for movement

	static const int MAX_BULLETS = 3;// assign max bullets
	Bullet* mBullets[MAX_BULLETS];// points bullets

	void HandleMovement();// Called when player is active to handle input
	void HandleFiring();// Called to handle bullet firing input

public:

	Enemy1(); // Loads a texture for the player, animation for the death of the player and bullets
	~Enemy1();

	void Visible(bool visible);// Sets player visible to true or false
	bool IsAnimating();// Find out if player is animating or not

	
	void Update();
	void Render();//Called to render the texture to the screen
};

#endif // !_ENEMY1_H