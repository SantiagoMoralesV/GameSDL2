// Animation.cpp                                               
// Extends the Texture class' functionality to handle animations   
// Uses the Texture class' spritesheet constructor 
#include "Animation.h"

Animation::Animation(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir)
	: Texture(filename, x, y, w, h)
{
	mTimer = Timer::Instance();

	mStartX = x;
	mStartY = y;

	mFrameCount = frameCount; 
	mAnimationSpeed = animationSpeed;
	mTimePerFrame = mAnimationSpeed / mFrameCount;
	mAnimationTimer = 0.0f;

	mAnimationDirection = animationDir;

	mAnimationDone = false;

	mWrapMode = loop;
}

Animation::~Animation()
{

}

void Animation::WrapMode(WRAP_MODE mode)
{
	mWrapMode = mode;
}

void Animation::ResetAnimation()
{
	// Resets the timer back to zero and animation done to false
	mAnimationTimer = 0.0f;
	mAnimationDone = false;
}

bool Animation::IsAnimating()
{
	// if animation is not done is animating will be true
	return !mAnimationDone;
}

void Animation::Update() {

	if (!mAnimationDone) {

		mAnimationTimer += mTimer->DeltaTime();

		if (mAnimationTimer >= mAnimationSpeed) {

			//Only loop if the wrap mode is loop
			if (mWrapMode == loop) {

				mAnimationTimer -= mAnimationSpeed;

			} else {

				mAnimationDone = true;
				mAnimationTimer = mAnimationSpeed - mTimePerFrame;
			}
		}

		if (mAnimationDirection == horizontal) {

			mClipRect.x = mStartX + (int)(mAnimationTimer / mTimePerFrame) * mWidth;

		}
		else {

			mClipRect.y = mStartY + (int)(mAnimationTimer / mTimePerFrame) * mHeight;
		}
	}
}
