// Input.cpp                                                    
// Handles all Input related functionality for keyboard and mouse.     
#include "Input.h"

//Initializing to NULL
Input* Input::sInstance = NULL;

Input * Input::Instance()
{
	// Create a new instance if no instance was created before
	if (sInstance == NULL)
		// create new instance
		sInstance = new Input();

	// return instance
	return sInstance;
}

void Input::Release()
{
	// delete instance and set it to NULL
	delete sInstance;
	sInstance = NULL;
}

bool Input::KeyDown(SDL_Scancode scanCode)
{
	return (mKeyboardState[scanCode] != 0);
}

bool Input::KeyPressed(SDL_Scancode scanCode)
{
	//returning true of the key was not pressed in the previous keyboard state but is pressed in the current one
	return !mPrevKeyboardState[scanCode] && mKeyboardState[scanCode];
}

bool Input::KeyReleased(SDL_Scancode scanCode)
{
	//returning true of the key was pressed in the previous keyboard state but is not pressed in the current one
	return mPrevKeyboardState[scanCode] && !mKeyboardState[scanCode];;
}

bool Input::MouseButtonDown(MOUSE_BUTTON button)
{
	Uint32 mask = 0;
	
	switch (button) {

	case left:

		mask = SDL_BUTTON_LMASK;
		break;

	case right:

		mask = SDL_BUTTON_RMASK;
		break;

	case middle:

		mask = SDL_BUTTON_MMASK;
		break;

	case back:

		mask = SDL_BUTTON_X1MASK;
		break;

	case forward:

		mask = SDL_BUTTON_X2MASK;
		break;
	}
	//return true if the mask exists in the current mouse state
	return ((mMouseState & mask) != 0);
}

bool Input::MouseButtonPressed(MOUSE_BUTTON button)
{
	Uint32 mask = 0;

	switch (button) {

	case left:

		mask = SDL_BUTTON_LMASK;
		break;

	case right:

		mask = SDL_BUTTON_RMASK;
		break;

	case middle:

		mask = SDL_BUTTON_MMASK;
		break;

	case back:

		mask = SDL_BUTTON_X1MASK;
		break;

	case forward:

		mask = SDL_BUTTON_X2MASK;
		break;
	}
	//return true if the mask does not exist in the previous mouse state, but exists in the current one
	return ((mPrevMouseState & mask == 0 ) && (mMouseState & mask) != 0);
}

bool Input::MouseButtonReleased(MOUSE_BUTTON button)
{
	Uint32 mask = 0;

	switch (button) {

	case left:

		mask = SDL_BUTTON_LMASK;
		break;

	case right:

		mask = SDL_BUTTON_RMASK;
		break;

	case middle:

		mask = SDL_BUTTON_MMASK;
		break;

	case back:

		mask = SDL_BUTTON_X1MASK;
		break;

	case forward:

		mask = SDL_BUTTON_X2MASK;
		break;
	}
	//return true if the mask exists in the previous mouse state, but does not exist in the current one
	return ((mPrevMouseState & mask) != 0) && ((mMouseState & mask) == 0);
}

Vector2 Input::MousePos()
{
	//Converting the mouse position into a Vector2 for ease of use since all entities use Vector2
	return Vector2((float)mMouseXPos, (float)mMouseYPos);
}

void Input::Update()
{
	//Updating the mouse state to get the key states of the current frame
	mMouseState = SDL_GetMouseState(&mMouseXPos, &mMouseYPos);
}

void Input::UpdatePrevInput()
{
	//Copying the keyboard state into the previous keyboard state array at the end of the frame
	memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
	//Setting the previous mouse state as the current mouse state at the end of the frame
	mPrevMouseState = mMouseState;
}

Input::Input()
{
	mKeyboardState = SDL_GetKeyboardState(&mKeyLength);
	//Setting mPrevKeyboardState to be the same length as mKeyboardState
	mPrevKeyboardState = new Uint8[mKeyLength];
	//Copying the contents of mKeyboardState into mPrevKeyboardState so that it contains data on the first frame
	memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
}


Input::~Input()
{
	//Clearing the previous keyboard state array
	delete[]mPrevKeyboardState;
	mPrevKeyboardState = NULL;
}
