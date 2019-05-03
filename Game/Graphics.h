#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <SDL.h>
#include <iostream>

class Graphics
{
public:

	// constants for the width and height of the screen is
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;

	// it returns instance
	static Graphics* Instance();
	// clear any static memory allocation
	static void Release();
	// Gives us back the initialized value
	static bool Initialized();

	// refresh back buffer once is ready to render
	void Render();

private:
	// singleton class
	Graphics();
	~Graphics();

	// Initializes everything
	bool Init();
	
	// initiliaze instance
	static Graphics* sInstance;
	//set to true if the graphics initialize properly otherwise will be false
	static bool sInitialized;

	// members variables
	// the window we will be rendering to
	SDL_Window* sdlWindow;
	// hardware accelerated texture rendering 
	SDL_Surface* mBackBuffer;

};

#endif