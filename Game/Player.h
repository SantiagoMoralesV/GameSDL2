//Player.h
// Creates a Player assigns input, position and movement speed
#ifndef _PLAYER_H
#define _PLAYER_H
#include "Animation.h"
#include "Input.h"
#include "Bullet.h"

class Player : public GameObject
{
private:
	//Used to get the deltatime to handle movement on the player
	Timer* mTimer;
	//Used to get the input on the player
	Input* mInput;

	bool mVisible;// if true show player ship
	bool mAnimating;// if true show death player animation

	Texture* mShip;// create a texture for player

	Animation* mDeathAnimation;// create a death animation for player

	float mMoveSpeed;// set speed for texture
	Vector2 mMoveBounds;// set bounds for movement

	static const int MAX_BULLETS = 3;// assign max bullets
	Bullet* mBullets[MAX_BULLETS];// points bullets

	void HandleMovement();// Called when player is active to handle input
	void HandleFiring();// Called to handle bullet firing input


public:

	Player(); // Loads a texture for the player, animation for the death of the player and bullets
	~Player();

	void Visible(bool visible);// Sets player visible to true or false
	bool IsAnimating();// Find out if player is animating or not

	void WasHit();// Reset animation 
	void Update();
	void Render();//Called to render the texture to the screen
};

#endif

