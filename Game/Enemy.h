#ifndef _ENEMY_H
#define _ENEMY_H
#include "Animation.h"
#include "Input.h"
#include "Bullet.h"

class Enemy : public GameObject
{
private:

	Timer* mTimer;
	Input* mInput;

	bool mVisible;
	bool mAnimating;

	Texture* mShipE;

	Animation* mDeathAnimation;

	float mMoveSpeed;
	Vector2 mMoveBounds;

	static const int MAX_BULLETS = 3;
	Bullet* mBullets[MAX_BULLETS];

	void HandleMovement();
	void HandleFiring();


public:

	Enemy();
	~Enemy();

	void Visible(bool visible);
	bool IsAnimating();

	void WasHit();

	void Update();

	void Render();
};
#endif
