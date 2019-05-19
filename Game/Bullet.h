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

	const int OFFSCREEN_BUFFER = 10;

	Timer* mTimer;

	float mSpeed;

	Texture* mTexture;

public:

	void Fire(Vector2 pos);
	void Reload();

	void Update1();
	void Update2();
	void Render();
};

#endif 