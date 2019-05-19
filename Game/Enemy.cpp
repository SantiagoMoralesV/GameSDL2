#include "Enemy.h"



Enemy::Enemy()
{
	mTimer = Timer::Instance();
	mInput = Input::Instance();

	mVisible = false;
	mAnimating = false;

	mShipE = new Texture("enemyGreen2.png");
	mShipE->Parent(this);
	mShipE->Pos(VEC2_ZERO);

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


Enemy::~Enemy()
{
	mTimer = NULL;
	mInput = NULL;

	delete mShipE;
	mShipE = NULL;

	delete mDeathAnimation;
	mDeathAnimation = NULL;

	for (int i = 0; i < MAX_BULLETS; i++) {

		delete mBullets[i];
		mBullets[i] = NULL;

	}
}

void Enemy::HandleMovement() {

	if (mInput->KeyDown(SDL_SCANCODE_D)) {


		Translate(VEC2_RIGHT*mMoveSpeed*mTimer->DeltaTime(), world);
	}
	else if (mInput->KeyDown(SDL_SCANCODE_A)) {

		Translate(-VEC2_RIGHT*mMoveSpeed*mTimer->DeltaTime(), world);
	}

	Vector2 pos = Pos(local);
	if (pos.x < mMoveBounds.x)
		pos.x = mMoveBounds.x;
	else if (pos.x > mMoveBounds.y)
		pos.x = mMoveBounds.y;

	Pos(pos);
}

void Enemy::HandleFiring()
{
	if (mInput->KeyPressed(SDL_SCANCODE_T)) {

		for (int i = 0; i < MAX_BULLETS; i++) {

			if (!mBullets[i]->Active()) {

				mBullets[i]->Fire(Pos());
				break;
			}
		}
	}
}

void Enemy::Visible(bool visible) {

	mVisible = visible;

}

bool Enemy::IsAnimating() {

	return mAnimating;
}

void Enemy::WasHit()
{
	mDeathAnimation->ResetAnimation();
	mAnimating = true;
}

void Enemy::Update() {

	if (mAnimating) {

		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();

	}
	else {

		if (Active()) {

			HandleMovement();
			HandleFiring();
		}
	}

	for (int i = 0; i < MAX_BULLETS; i++)
		mBullets[i]->Update2();

}

void Enemy::Render() {

	if (mVisible) {

		if (mAnimating) {

			mDeathAnimation->Render();

		}
		else {

			mShipE->Render();
		}
	}
	for (int i = 0; i < MAX_BULLETS; i++) {

		mBullets[i]->Render();
	}
}