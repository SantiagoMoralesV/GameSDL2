#include "PhysEntity.h"

PhysEntity::PhysEntity()
{
	mBroadPhaseCollider = nullptr;
}

PhysEntity::~PhysEntity()
{
	for(int i = 0; i < mColliders.size(); i++) {

		delete mColliders[i];
		mColliders[i] = nullptr;
	}
	// clear the vector
	mColliders.clear();

	//clearing the collider
	if (mBroadPhaseCollider) {

		delete mBroadPhaseCollider;
		mBroadPhaseCollider = nullptr;
	}
}

unsigned long PhysEntity::GetId()
{
	return mId;
}

void PhysEntity::AddCollider(Collider* collider, Vector2 localPos) {

	collider->Parent(this);
	collider->Pos(localPos);
	// Add collider to our colliders vector
	mColliders.push_back(collider);

	if (mColliders.size() > 1) {

		float furthestDist = mColliders[0]->GetFurthestPoint().Magnitude();
		float dist = 0.0f;
		for (int i = 0; i < mColliders.size(); i++) {

			dist = mColliders[i]->GetFurthestPoint().Magnitude();
			if (dist > furthestDist) {

				furthestDist = dist;
			}
		}

		delete mBroadPhaseCollider;
	}
}

void PhysEntity::Render() {

	for (int i = 0; i < mColliders.size(); i++){
		
		mColliders[i]->Render();
	}

	if (mBroadPhaseCollider)
		mBroadPhaseCollider->Render();
}