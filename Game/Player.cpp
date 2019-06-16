// Player.cpp
// Creates a Player assigns input, position and movement speed
#include "Player.h"


Player::Player()
{
	mTimer = Timer::Instance();// Timer Instance
	mInput = Input::Instance();// Input Instance
	mAudio = AudioManager::Instance();// Audio Instance

	mVisible = false;// animation visibility start as false since is only triggered when player is hit
	mAnimating = false; // animation start as false since is only triggered when player is hit

	mScore = 0;
	mLives = 2;

	mShip = new Texture("sheet.png", 144, 157, 102, 83);
	mShip->Parent(this);
	mShip->Pos(VEC2_ZERO);

	mMoveSpeed = 300.0f;
	mMoveBounds = Vector2(55.0f, 740);

	//Death animation spritesheet played horizontally
	mDeathAnimation = new Animation("explosion2.png", 0, 0, 112, 107, 4, 1.0f, Animation::horizontal);
	mDeathAnimation->Parent(this);// It shows animation in the player texture
	mDeathAnimation->Pos(VEC2_ZERO);//The position where the animation is played
	mDeathAnimation->WrapMode(Animation::once);// repeat the animation only once

	// creating the player bullets
	for (int i = 0; i < MAX_BULLETS; i++) {

		mBullets[i] = new Bullet();
	}
}


Player::~Player()
{
	mTimer = NULL;// sets timer to NULL
	mInput = NULL;// sets input to NULL
	mAudio = NULL;// sets Audio to NULL

	delete mShip;// deletes the texture mship and sets it to NULL
	mShip = NULL;

	delete mDeathAnimation;// deletes the Animation mDeathAnimation and sets it to NULL
	mDeathAnimation = NULL;

	//deletes bullets loop and set them to NULL
	for (int i = 0; i < MAX_BULLETS; i++) {

		delete mBullets[i];
		mBullets[i] = NULL;

	}
}

void Player::HandleMovement() {

	if (mInput->KeyDown(SDL_SCANCODE_RIGHT)) {

		Translate(VEC2_RIGHT*mMoveSpeed*mTimer->DeltaTime());
	}
	else if (mInput->KeyDown(SDL_SCANCODE_LEFT)) {

		Translate(-VEC2_RIGHT*mMoveSpeed*mTimer->DeltaTime());
	}

	Vector2 pos = Pos(local);
	if (pos.x < mMoveBounds.x)
		pos.x = mMoveBounds.x;
	else if (pos.x > mMoveBounds.y)
		pos.x = mMoveBounds.y;

	Pos(pos);
}

void Player::HandleFiring()
{
	// Player able to fire once the space is pressed
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {

		for (int i = 0; i < MAX_BULLETS; i++) {
			//if bullet is not active
			if (!mBullets[i]->Active()) {
				// fire bullets
				mBullets[i]->Fire(Pos());
				// played bullet sound
				mAudio->PlaySFX("bullet.wav");
				break;
			}
		}
	}
}

void Player::Visible(bool visible) {

	mVisible = visible;

}

bool Player::IsAnimating() {

	return mAnimating;
}

int Player::Score()
{
	return mScore;
}

int Player::Lives()
{
	return mLives;
}

void Player::AddScore(int change)
{
	mScore += change;
}

void Player::WasHit()
{
	// decrease one live of the player
	mLives--;
	// Resets the timer back to zero and animation done to false
	mDeathAnimation->ResetAnimation();
	mAnimating = true;
	//play explosion sound effect
	mAudio->PlaySFX("explosion.wav");

}

void Player::Update() {

	if (mAnimating) {

		// Once the animation is playing, there is no player movement
		mDeathAnimation->Update();
		// Plays death animation
		// Once animating is false player will return to player active
		mAnimating = mDeathAnimation->IsAnimating();

	} else {

		if (Active()) {

			// Once player is active, able to handle movement and firing 
			HandleMovement();
			HandleFiring();
		}
	}
	// Updating the bullets
	for (int i = 0; i < MAX_BULLETS; i++) 
		mBullets[i]->Update1();
	
}

void Player::Render() {

	if (mVisible) {

		if (mAnimating) {

			// if player is visibible and animating is true render death animation on the player
			mDeathAnimation->Render();

		}
		else {

			// renders the player ship
			mShip->Render();
		}
	}
	// rendering bullets
	for (int i = 0; i < MAX_BULLETS; i++) {

		mBullets[i]->Render();
	}
}