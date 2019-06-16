// Graphics.h
// Handles the initialization of the graphics related to SDL libraries
// and their release
// Handles texture as well

#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <SDL.h>
#include <iostream>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>


class Graphics
{
public:

	// The Width of the game's window
	static const int SCREEN_WIDTH = 1024;
	// The Height of the game's window
	static const int SCREEN_HEIGHT = 700;
	// The title of the game's window
	const char* WINDOW_TITLE = "Target Hunt";

	//Returns a pointer to the class instance 
	static Graphics* Instance();

	// Releases the class instance and sets it back to NULL 
	// Sets Initialized to false
	static void Release();

	// Is true if the SDL libraries initialized correctly
	static bool Initialized();

	// Loads a texture from file using the given path
	SDL_Texture* LoadTexture(std::string path);

	SDL_Texture* CreateTextTexture(TTF_Font*  font, std::string text, SDL_Color color);

	// Clears all rendered textures from the back buffer
	// usually used at the begining of the frame's render
	void ClearBackBuffer();


	//Draws the given texture to the back buffer
	void DrawTexture(SDL_Texture* tex, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Draws a line
	void DrawLine(float startX, float startY, float endX, float endY);

	// Refreshes the back buffer
	// Usually called at then end of the frame's render
	void Render();

private:
	
	// Contructor is private so that Instance() must be used to get an instance when needed  
	Graphics(); 
	// Destructor is private so that the instance can only be destroyed using Release()  
	~Graphics();

	// Used to initialize all the SDL graphic libraries
	// Returns true if all libraries initialized correctly
	// Returns false otherwise to be handled by the GameManager
	bool Init();
	
	// Needed to make GameManager a singleton class
	static Graphics* sInstance;
	// Is set to true if all the graphics libraries initialized correctly
	static bool sInitialized;

	// Members variables
	//The window created using SDL
	SDL_Window* sdlWindow;
	
	//The renderer used to render all textures
	SDL_Renderer* mRenderer;

};

#endif