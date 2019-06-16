#include "GameObject.h"


GameObject::GameObject(Vector2 pos) {

	mPos = pos;
	mRotation = 0.0f;
	mActive = true;
	mParent = NULL;
	mScale = VEC2_ONE;
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

	Vector2 parentScale = mParent->Scale(world);
	//The object's local position is rotated by the parent's rotation
	Vector2 rotPos = RotateVector(Vector2(mPos.x * parentScale.x, mPos.y * parentScale.y), mParent->Rotation(local));

	//The final position also depends on the parent's scale (if the parent is scaled up, the object should be further away from the parent)
	return mParent->Pos(world) + rotPos;
}

void GameObject::Rotation(float r) {

	mRotation = r;

	//Wraps the angle between 0 and 360 degrees, addition and subtraction is sed to avoid snapping
	//Updated to deal with degrees higher than 360 and -360
	if (mRotation > 360.0f) {

		int mul = mRotation / 360;
		mRotation -= 360.0f * mul;

	}
	else if (mRotation < 0.0f) {

		int mul = (mRotation / 360) - 1;
		mRotation -= 360.0f * mul;
	}
}

float GameObject::Rotation(SPACE space) {

	if (space == local || mParent == NULL)
		return mRotation;

	return mParent->Rotation(world) + mRotation;
}

void GameObject::Scale(Vector2 scale) {

	mScale = scale;
}

Vector2 GameObject::Scale(SPACE space) {

	if (space == local || mParent == NULL)
		return mScale;

	Vector2 scale = mParent->Scale(world);
	scale.x *= mScale.x;
	scale.y *= mScale.y;

	return scale;
}

void GameObject::Active(bool active) {

	mActive = active;
}

bool GameObject::Active() {

	return mActive;
}

void GameObject::Parent(GameObject* parent) {

	//If the parent is removed, The Position/Rotation/Scale are the GameEntity's world values, to keep the object looking the same after the removal of the parent;
	if (parent == NULL) {

		mPos = Pos(world);
		mScale = Scale(world);
		mRotation = Rotation(world);

	}
	else {

		//If the object already has a parent, remove the current parent to get it ready to be the child for the new parent
		if (mParent != NULL)
			Parent(NULL);

		Vector2 parentScale = parent->Scale(world);

		//Setting the local position to be relative to the new parent (while maintaining the same world position as before)
		mPos = RotateVector(Pos(world) - parent->Pos(world), -parent->Rotation(world));
		mPos.x /= parentScale.x;
		mPos.y /= parentScale.y;

		//Setting the local rotation to be relative to the new parent (while maintaining the same world rotation as before)
		mRotation = mRotation - parent->Rotation(world);

		//Setting the new scale to be relative to the new parent (while maintaining the same world scale as before)
		mScale = Vector2(mScale.x / parentScale.x, mScale.y / parentScale.y);
	}

	mParent = parent;
}

GameObject* GameObject::Parent() {

	return mParent;
}

void GameObject::Translate(Vector2 vec) {

	mPos += vec;
}

void GameObject::Rotate(float amount) {

	mRotation += amount;
}

void GameObject::Update() {


}

void GameObject::Render() {


}
