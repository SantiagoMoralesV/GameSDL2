//Bullet.cpp
//Create bullets used for Player and Enemy
#include "Bullet.h"
#include "BoxCollider.h"

Bullet::Bullet()
{
	mTimer = Timer::Instance();

	mSpeed = 1000.0f;

	mTexture = new Texture("laserRed03.png");
	mTexture->Parent(this);
	mTexture->Pos(VEC2_ZERO);

	Reload();

	AddCollider(new BoxCollider(mTexture->ScaledDimensions));
}


Bullet::~Bullet()
{
	mTimer = NULL;

	delete mTexture;
	mTexture = NULL;
}

void Bullet::Fire(Vector2 pos) {
	// where we set the bullet once is fired
	Pos(pos);
	Active(true);
}

void Bullet::Reload() {

	Active(false);
}

void Bullet::Update1() {

	if(Active()){
		// direction of the bullet up
		Translate(-VEC2_UP * mSpeed * mTimer->DeltaTime());

		Vector2 pos = Pos();
		// checks the bounds if the bullet is offscreen or not 
		if (pos.y < -OFFSCREEN_BUFFER || pos.y > Graphics::Instance()->SCREEN_HEIGHT + OFFSCREEN_BUFFER) {
			// if it is Offscreen just reload
			Reload();
		}
	}
}
void Bullet::Update2() {

	if (Active()) {

		Translate(VEC2_UP * mSpeed * mTimer->DeltaTime());

		Vector2 pos = Pos();

		if (pos.y < -OFFSCREEN_BUFFER || pos.y > Graphics::Instance()->SCREEN_HEIGHT + OFFSCREEN_BUFFER) {

			Reload();
		}
	}
}

void Bullet::Render() {

	if (Active()) {
		// bullet render
		mTexture->Render();
		PhysEntity::Render();
	}
}