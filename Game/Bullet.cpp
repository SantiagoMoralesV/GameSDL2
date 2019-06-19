//Bullet.cpp
//Create bullets used for Player and Enemy
#include "Bullet.h"
#include "BoxCollider.h"

Bullet::Bullet()
{
	mTimer = Timer::Instance();
	//bullet speed
	mSpeed = 1000.0f;
	// new texture for the bullet
	mTexture = new Texture("laserRed03.png");
	//relative to its parent
	mTexture->Parent(this);
	// position of the the bullet
	mTexture->Pos(VEC2_ZERO);

	Reload();
	// scales dimension of the bullet
	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));
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
		// direction of the bullet down calld by enemy
		Translate(VEC2_UP * mSpeed * mTimer->DeltaTime());

		Vector2 pos = Pos();
		// checks the bound if the bullet is offscreen or not
		if (pos.y < -OFFSCREEN_BUFFER || pos.y > Graphics::Instance()->SCREEN_HEIGHT + OFFSCREEN_BUFFER) {
			// if offscreen reload
			Reload();
		}
	}
}

void Bullet::Render() {

	if (Active()) {
		// bullet render
		mTexture->Render();
		//renders the box collider
		PhysEntity::Render();
	}
}