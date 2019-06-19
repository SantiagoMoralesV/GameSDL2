#ifndef _BOXCOLLIDER_H
#define _BOXCOLLIDER_H
#include "Collider.h"

class BoxCollider : public Collider
{

private:
	// we need 4 vertices for our box to check the collision
	static const int MAX_VERTS = 4;
	
	GameObject* mVerts[MAX_VERTS];
	// takes index and position
	void AddVert(int index, Vector2 pos);

public:
	// Constructor takes size which is the box size
	BoxCollider(Vector2 size);
	~BoxCollider();
	// how far is the vertex in the box from the center of the object attached too
	Vector2 GetFurthestPoint() override;
};

#endif // !_BOXCOLLIDER_H

