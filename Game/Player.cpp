// Player.cpp
// Creates a Player assigns input, position and movement speed
#include "Player.h"


Player::Player()
{
	mTimer = Timer::Instance();
	mInput = Input::Instance();

	mVisible = false;
	mAnimating = false; 

	mShip = new Texture("sheet.png", 144, 157, 102, 83);
	//mShip = new Texture("playerShip1.png");
	mShip->Parent(this);
	mShip->Pos(VEC2_ZERO);

	mMoveSpeed = 300.0f;
	mMoveBounds = Vector2(50.0f, 750);

	mDeathAnimation = new Animation("explosion.png", 0, 0, 38, 42, 4, 1.0f, Animation::horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Pos(VEC2_ZERO);
	mDeathAnimation->WrapMode(Animation::once);

	for (int i = 0; i < MAX_BULLETS; i++) {

		mBullets[i] = new Bullet();
	}
}


Player::~Player()
{
	mTimer = NULL;
	mInput = NULL;

	delete mShip;
	mShip = NULL;

	delete mDeathAnimation;
	mDeathAnimation = NULL;

	for (int i = 0; i < MAX_BULLETS; i++) {

		delete mBullets[i];
		mBullets[i] = NULL;

	}
}

void Player::HandleMovement() {

	if (mInput->KeyDown(SDL_SCANCODE_RIGHT)) {


		Translate(VEC2_RIGHT*mMoveSpeed*mTimer->DeltaTime(), world);
	}
	else if (mInput->KeyDown(SDL_SCANCODE_LEFT)) {

		Translate(-VEC2_RIGHT*mMoveSpeed*mTimer->DeltaTime(), world);
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
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {

		for (int i = 0; i < MAX_BULLETS; i++) {
			
			if (!mBullets[i]->Active()) {

				mBullets[i]->Fire(Pos());
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

void Player::WasHit()
{
	mDeathAnimation->ResetAnimation();
	mAnimating = true;
}

void Player::Update() {

	if (mAnimating) {

		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();

	} else {

		if (Active()) {

			HandleMovement();
			HandleFiring();
		}
	}

	for (int i = 0; i < MAX_BULLETS; i++) 
		mBullets[i]->Update1();
	
}

void Player::Render() {

	if (mVisible) {

		if (mAnimating) {

			mDeathAnimation->Render();

		}
		else {

			mShip->Render();
		}
	}
	for (int i = 0; i < MAX_BULLETS; i++) {

		mBullets[i]->Render();
	}
}