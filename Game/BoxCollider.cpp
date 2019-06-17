#include "BoxCollider.h"

BoxCollider::BoxCollider(Vector2 size)
	: Collider(ColliderType::Box)
{
	// all the Box vertices
	AddVert(0, Vector2(-0.5f * size.x, -0.5f * size.y));
	AddVert(1, Vector2( 0.5f * size.x, -0.5f * size.y));
	AddVert(2, Vector2(-0.5f * size.x,  0.5f * size.y));
	AddVert(3, Vector2( 0.5f * size.x,  0.5f * size.y));

	if (DEBUG_COLLIDERS) {
		// Box texture
		SetDebugTexture(new Texture("boxCollider.png"));
		// Scale texture to be the same as the box texture
		mDebugTexture->Scale(size / 100.0f);
	}
}


BoxCollider::~BoxCollider()
{
	// delete the 4 vertices created
	for (int i = 0; i < MAX_VERTS; i++) {

		delete mVerts[i];
		mVerts[i] = nullptr;
	}
}

Vector2 BoxCollider::GetFurthestPoint() {

	// get the local position of the collider relative to the player
	Vector2 localPos = Pos(GameObject::local);

	// assuming that the first index is the furthest one to start off
	int furthestIndex = 0;
	// getting the magnitute of the two distances finding the furthest vertex
	float dist = (localPos + mVerts[0]->Pos(GameObject::local)).MagnitudeSqr();
	float otherDist = 0.0f;

	for (int i = 0; i < MAX_VERTS; i++) {

		otherDist = (localPos + mVerts[i]->Pos(GameObject::local)).MagnitudeSqr();

		if (otherDist > dist) {
			// furthest index
			furthestIndex = i;
			dist = otherDist;
		}
	}
	// returning the furthest point
	return localPos + mVerts[furthestIndex]->Pos(GameObject::local);
}

void BoxCollider::AddVert(int index, Vector2 pos) {
	
	// Adding the position of the vert into the position of the Game Object
	mVerts[index] = new GameObject(pos);
	mVerts[index]->Parent(this);
}