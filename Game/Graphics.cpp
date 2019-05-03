#include "Graphics.h"

// Initialize the two static variables
Graphics* Graphics::sInstance = NULL;
bool Graphics::sInitialized = false;

Graphics * Graphics::Instance()
{
	// if instance was not created before
	if (sInstance == NULL) {
		// create new instance
		sInstance = new Graphics();
	}
	// return instance
	return sInstance;
}

void Graphics::Release()
{
	// delete instance and set it to NULL
	delete sInstance;
	sInstance = NULL;
	// set initialized to false
	sInitialized = false;

}

bool Graphics::Initialized()
{
	// returns initiliazed variable
	return sInitialized;
}
Graphics::Graphics()
{
	// variable not initialized yet
	mBackBuffer = NULL;

	// sInitialized variable is going to equal to the Init function
	sInitialized = Init();

}

Graphics::~Graphics()
{
	// Destroys the window created
	SDL_DestroyWindow(sdlWindow);
	// set SDl window to NULL
	sdlWindow = NULL;
	// call SDL function to quit SDL
	SDL_Quit();
}

bool Graphics::Init()
{
	if ((SDL_INIT_EVERYTHING) < 0 ){

		// print a failed message on to the console window
		std::cout << "Initialize SDL - Failed" << SDL_GetError() << std::endl;
		return false;
	}
	
	// create the SDL window
	sdlWindow = SDL_CreateWindow("SDL Game", 
											SDL_WINDOWPOS_UNDEFINED, 
											SDL_WINDOWPOS_UNDEFINED, 
											SCREEN_WIDTH,
											SCREEN_HEIGHT, 
											SDL_WINDOW_SHOWN);

	// if something failed while creating the SDL window
	if (sdlWindow == NULL) {
		// print a failed message on to the console window
		std::cout << "Create Window - Failed" << SDL_GetError() << std::endl;
		return false;
	}

	mBackBuffer = SDL_GetWindowSurface(sdlWindow);
	
	return true;
}


void Graphics::Render()
{
	// it refreshes the SDL window
	SDL_UpdateWindowSurface(sdlWindow);
}


