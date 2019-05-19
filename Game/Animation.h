// Animation.h                                               
// Extends the Texture class' functionality to handle animations   
// Uses the Texture class' spritesheet constructor                 
#ifndef _ANIMATION_H
#define _ANIMATION_H
#include "Timer.h"
#include "Texture.h"

class Animation : public Texture
{
public:
	//WRAP_MODE enum - wrap mode used by the animation
	//once / loop 
	enum WRAP_MODE { once = 0, loop = 1 };

	//ANIM_DIR enum - The way the animation sprites are arranged in the spritesheet
	//horizontal / vertical
	enum ANIM_DIR { horizontal = 0, vertical = 1};

	//Loads a texture from from file (relative to the exe path)
	//Supports spritesheets
	//x - Starting pixel's X on the spritesheet
	//y - Starting pixel's Y on the spritesheet
	//w - The width of the clipped sprite
	//h - The height of the clipped sprite
	//frameCount - The number of frames in the animation
	//animationSpeed - How long it takes to run the animation in seconds
	//animationDirection - How the animation sprites are arranges in the spritesheet
	//---------------------------------------------------------------------------------
	Animation(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir);
	~Animation();

	//Sets the wrap mode of the animation
	void WrapMode(WRAP_MODE mode);

	void ResetAnimation();

	bool IsAnimating();

	//Used to update the animation frames and loop the animation if needed
	void Update();

private: 
	//Used to get the deltatime to update the animation
	Timer* mTimer;


	int mStartX;//the first frame's starting pixel's X values on the spritesheet
	int mStartY;//the first frame's starting pixel's Y values on the spritesheet

	float mAnimationTimer; //Used to keep track of how long the current animation frame has been on screen
	float mAnimationSpeed; //Used to determine the speed of the animation
	float mTimePerFrame; //Stores how long each animation frame should be on screen

	int mFrameCount;//Stores the number of animation frames in the animation

	WRAP_MODE mWrapMode;//Stores the wrap mode
	ANIM_DIR mAnimationDirection;//Stores the animation direction

	bool mAnimationDone;//Is set to true only if the wrap mode is once and the last frame of the animation is reached
	
};
#endif
