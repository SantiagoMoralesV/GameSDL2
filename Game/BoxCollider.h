#ifndef _BOXCOLLIDER_H
#define _BOXCOLLIDER_H
#include "Collider.h"

class BoxCollider : public Collider
{

private:
	// we need 4 vertices for our box to check the collision
	static const int MAX_VERTS = 4;
	
	GameObject* mVerts[MAX_VERTS];
	
	void AddVert(int index, Vector2 pos);

public:
	// Constructor takes size which is the box size
	BoxCollider(Vector2 size);
	~BoxCollider();
};

#endif // !_BOXCOLLIDER_H

