#include "Enemy1.h"
#include "BoxCollider.h"

Enemy1::Enemy1()
{
	mTimer = Timer::Instance();// Timer Instance
	mInput = Input::Instance();// Input Instance
	mAudio = AudioManager::Instance();// Audio Instance

	mVisible = false;// animation visibility start as false since is only triggered when player is hit
	mAnimating = false; // animation start as false since is only triggered when player is hit

	mEnemy1 = new Texture("enemyGreen2.png");
	mEnemy1->Parent(this);
	mEnemy1->Pos(VEC2_ZERO);

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

	//AddCollider(new BoxCollider(mEnemy1->ScaledDimensions()));
	AddCollider(new BoxCollider(Vector2(50.0f, 80.0f)));
	AddCollider(new BoxCollider(Vector2(30.0f, 30.0f)), Vector2(40.0f, 0.0f));
	AddCollider(new BoxCollider(Vector2(30.0f, 30.0f)), Vector2(-40.0f, 0.0f));
}


Enemy1::~Enemy1()
{
	mTimer = NULL;// sets timer to NULL
	mInput = NULL;// sets input to NULL
	mAudio = NULL;// sets Audio to NULL

	delete mEnemy1;// deletes the texture mship and sets it to NULL
	mEnemy1 = NULL;

	delete mDeathAnimation;// deletes the Animation mDeathAnimation and sets it to NULL
	mDeathAnimation = NULL;

	//deletes bullets loop and set them to NULL
	for (int i = 0; i < MAX_BULLETS; i++) {

		delete mBullets[i];
		mBullets[i] = NULL;

	}
	
}

void Enemy1::HandleMovement() {

	if (mInput->KeyDown(SDL_SCANCODE_D)) {
		// if pressed right arrow moves to right
		Translate(VEC2_RIGHT*mMoveSpeed*mTimer->DeltaTime());
	}
	else if (mInput->KeyDown(SDL_SCANCODE_A)) {
		// if pressed lefty arrow moves to left
		Translate(-VEC2_RIGHT*mMoveSpeed*mTimer->DeltaTime());
	}
	// bounds of the movement enemy
	Vector2 pos = Pos(local);
	if (pos.x < mMoveBounds.x)
		pos.x = mMoveBounds.x;
	else if (pos.x > mMoveBounds.y)
		pos.x = mMoveBounds.y;

	Pos(pos);
}

void Enemy1::HandleFiring()
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

void Enemy1::Visible(bool visible) {

	mVisible = visible;

}

bool Enemy1::IsAnimating() {
	// return if is animating
	return mAnimating;
}


	void Enemy1::Update() {

	if (mAnimating) {

		// Once the animation is playing, there is no player movement
		mDeathAnimation->Update();
		// Plays death animation
		// Once animating is false player will return to player active
		mAnimating = mDeathAnimation->IsAnimating();

	}
	else {

		if (Active()) {

			// Once player is active, able to handle movement and firing 
			HandleMovement();
			HandleFiring();
		}
	}
	// Updating the bullets
	for (int i = 0; i < MAX_BULLETS; i++)
		mBullets[i]->Update2();

}

void Enemy1::Render() {

	if (mVisible) {

		if (mAnimating) {

			// if player is visibible and animating is true render death animation on the player
			mDeathAnimation->Render();

		}
		else {

			// renders the player ship
			mEnemy1->Render();
		}
	}
	// rendering bullets
	for (int i = 0; i < MAX_BULLETS; i++) {

		mBullets[i]->Render();
	}
	//renders box colliders
	PhysEntity::Render();
}