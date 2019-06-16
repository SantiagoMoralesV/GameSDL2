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


void BoxCollider::AddVert(int index, Vector2 pos) {
	
	// Adding the position of the vert into the position of the Game Object
	mVerts[index] = new GameObject(pos);
	mVerts[index]->Parent(this);
}