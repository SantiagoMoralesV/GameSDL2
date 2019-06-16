#include "PhysEntity.h"

PhysEntity::PhysEntity()
{

}

PhysEntity::~PhysEntity()
{
	for(int i = 0; i < mColliders.size(); i++) {

		delete mColliders[i];
		mColliders[i] = nullptr;
	}
	// clear the vector
	mColliders.clear();
}

void PhysEntity::AddCollider(Collider* collider, Vector2 localPos) {

	collider->Parent(this);
	collider->Pos(localPos);
	// Add collider to our colliders vector
	mColliders.push_back(collider);
}

void PhysEntity::Render() {

	for (int i = 0; i < mColliders.size(); i++){
		
		mColliders[i]->Render;
	}
}