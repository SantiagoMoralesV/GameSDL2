//Bullet.h
//Create bullets used for Player and Enemy
#ifndef _BULLET_H
#define _BULLET_H
#include "Texture.h"
#include "Timer.h"

class Bullet : public GameObject
{
public:

	Bullet();
	~Bullet();

private:

	//Bullet disable if is off the screen by 10px
	const int OFFSCREEN_BUFFER = 10;
	// Used to get the deltatime to handle the bullet
	Timer* mTimer;

	// Bullet speed
	float mSpeed;

	//Graphics for the Bullet
	Texture* mTexture;

public:

	// Called when firing a bullet 
	void Fire(Vector2 pos);
	// When off screen or has hit the enemy called Reload
	void Reload();

	void Update1();// Bullet direction up (called by the player)
	void Update2();// Bullet direction down (called by the player)
	void Render();// Renders Bullet
};

#endif 