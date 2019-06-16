#ifndef _COLLIDER_H
#define _COLLIDER_H
#include "Texture.h"


class Collider : public GameObject
{

public:
	// All the types of colliders in the Game
	enum class ColliderType {

		Box,
		Circle
	};

protected:

	ColliderType mType;
	// if DEBUG_COLLIDERS it is true render our debug textures if false not render
	static const bool DEBUG_COLLIDERS = true;
	// mDebugTexture Texture 
	Texture* mDebugTexture;

	void SetDebugTexture(Texture* texture);

public:

	Collider(ColliderType type);
	virtual ~Collider();

	virtual void Render();
};

#endif // !_COLLIDER_H