#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H
#include "MathHelper.h"

class GameObject {

public:

	enum SPACE {local = 0, world = 1};

	GameObject(float x = 0.0f, float y = 0.0f);
	~GameObject();

	void Pos(Vector2 pos);
	Vector2 Pos(SPACE space = world);

	void Rotation(float rotation);
	float Rotation(SPACE space = world);

	void Active(bool active);
	bool Active();

	void Parent(GameObject* parent);
	GameObject* Parent();

	virtual void Update();
	virtual void Render();

private:

	Vector2 mPos;
	float mRotation;

	bool mActive;
	GameObject* mParent;

	
};

#endif 
