#include "GameObject.h"


GameObject::GameObject(float x, float y) {

	mPos.x = x;
	mPos.y = y;
	mRotation = 0.0f;
	mActive = true;
	mParent = NULL;
}

GameObject::~GameObject() {

	mParent = NULL;
}

void GameObject::Pos(Vector2 pos) {

	mPos = pos;
}

Vector2 GameObject::Pos(SPACE space) {

	if (space == local || mParent == NULL)

		return mPos;

	return mParent->Pos(world) + RotateVector(mPos, mParent->Rotation(local));
}

void GameObject::Rotation(float r) {

	mRotation = r;

	// Wraps the angle between 0 and 360 degrees, addition and subtraction is set to avoid snapping
	// Updated to deal with degrees higher than 360 and -360
	if (mRotation > 360.f)
		mRotation -= 360.0f;

	if (mRotation < 0.0f)
		mRotation += 360.0f;

}

float GameObject::Rotation(SPACE space) {

	if (space == local || mParent == NULL)
		return mRotation;

	return mParent->Rotation(world) + mRotation;
}

void GameObject::Active(bool active) {
	
	mActive = active;
}

bool GameObject::Active()
{
	return mActive;
}

void GameObject::Parent(GameObject * parent)
{
	//If the parent is removed, The Position/Rotation are the GameObject's world values, to keep the object looking the same after the removal of the parent;
	if (parent == NULL) {
		
		mPos = Rotation(world);
		mRotation = Rotation(world);

	} else {
		
		//If the object already has a parent, remove the current parent to get it ready to be the child for the new parent
		if (mParent != NULL)
			Parent(NULL);

	}

	mParent = parent;
}

GameObject * GameObject::Parent()
{
	return mParent;
}

void GameObject::Update() {

}

void GameObject::Render() {

}

void GameObject::Translate(Vector2 vec, SPACE space)
{
	if(space == world){

		mPos += vec;
	}
	else {

		mPos += RotateVector(vec, Rotation());
	}
}

