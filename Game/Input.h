// Input.h                                                      
// Singleton                                                           
// Handles all Input related functionality for keyboard and mouse.     
#ifndef _INPUT_H
#define _INPUT_H
#include <SDL.h>
#include <string.h>
#include "MathHelper.h"

class Input
{

public:
	// MOUSE_BUTTON enum to describe left mouse button, right mouse button, .. and so on  
	enum MOUSE_BUTTON { left = 0, right, middle, back, forward };

	//Returns a pointer to the class instance
	static Input* Instance();
	//Releases the class instance and sets it back to NULL 
	static void Release();

	bool KeyDown(SDL_Scancode scanCode);// Returns true as long as the key given in scanCode is held down
	bool KeyPressed(SDL_Scancode scanCode);// Returns true only on the frame that the key given in scanCode is pressed down
	bool KeyReleased(SDL_Scancode scanCode);// Returns true only on the frame that the key given in scanCode is released

	bool MouseButtonDown(MOUSE_BUTTON button);// Returns true as long as the given mouse button is held down
	bool MouseButtonPressed(MOUSE_BUTTON button);// Returns true only on the frame that the given mouse button is pressed 
	bool MouseButtonReleased(MOUSE_BUTTON button);// Returns true only on the frame that the given mouse button is released 

	//Returns a Vector2 containing the current mouse position on screen
	Vector2 MousePos();

	void Update();//Updates the Input States (should be called once per frame before any input check)
	//Sets the current frame's key states as the previous key states (to be called in the LateUpdate)  
	//No input checks should be made in the current frame after this function is called
	void UpdatePrevInput();

private: 

	//Contructor is private so that Instance() must be used to get an instance when needed  
	Input();
	//Destructor is private so that the instance can only be destroyed using Release()  
	~Input();

	//Needed to make Input a singleton class
	static Input* sInstance;

	// Holds the keyboard key state of the last frame (used to catch key press and key release events)
	Uint8* mPrevKeyboardState;
	// Holds the keyboard key state of the current frame
	const Uint8* mKeyboardState;
	// The number of keys in the mKeyboardState array (used to copy the current keyboard state into the previous keyboard state)
	int mKeyLength;

	//Holds the mouse button state of the last frame (used to catch mouse button press and release events)
	Uint32 mPrevMouseState;
	//Holds the mouse button state of the current frame
	Uint32 mMouseState;

	//Used to retrieve the current mouse position using SDL_GetMouseState
	int mMouseXPos;
	int mMouseYPos;

};

#endif

