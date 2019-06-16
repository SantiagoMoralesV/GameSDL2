#ifndef _PHYSENTITY_H
#define _PHYSENTITY_H

#include <vector>
#include "Collider.h"

class PhysEntity : public GameObject
{
protected:

	// To be able to have multiple colliders to aproximate the shape of the object to have more accurate collision
	std::vector<Collider*> mColliders;

public:

	PhysEntity();
	//Clear all the colliders
	virtual ~PhysEntity();

	virtual void Render();

protected:

	//the local position of that collider we are passing with a default value of VEC2_Zero
	void AddCollider(Collider* collider, Vector2 localPos = VEC2_ZERO);

};

#endif