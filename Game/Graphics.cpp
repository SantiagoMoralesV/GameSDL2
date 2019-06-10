// Graphics.cpp
// Handles the initialization of the graphics related to SDL libraries
// and their release
// Handles texture as well
#include "Graphics.h"

// Initialize to NULL
Graphics* Graphics::sInstance = NULL;
//Initializing to false
bool Graphics::sInitialized = false;

Graphics * Graphics::Instance()
{
	//Create a new instance if no instance was created before
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
SDL_Texture * Graphics::LoadTexture(std::string path)
{

	SDL_Texture* tex = NULL;
	//load the image onto a surface
	SDL_Surface* surface = IMG_Load(path.c_str());

	//Handling image loading errors
	if (surface == NULL) {

		std::cout << "Image Load Error " << path.c_str()  << IMG_GetError() << std::endl;
		return tex;
	}
	//Converting the surface into a texture to be able to render it using the renderer
	tex = SDL_CreateTextureFromSurface(mRenderer, surface);

	//Handling texture creation errors
	if (tex == NULL) {

		std::cout << "Image Load Error " << SDL_GetError() << std::endl;
		return tex;
	}

	//free the surface since only the texture is needed
	SDL_FreeSurface(surface);

	return tex;

}

SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color) {

	//Render the text onto a surface using the provided font and color
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	//Handling font rendering errors
	if (surface == NULL) {

		std::cout << "Text Render Error: " << TTF_GetError() << std::endl;
		return NULL;
	}

	//Converting the surface into a texture to be able to render it using the renderer
	SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surface);
	//Handle texture creation errors
	if (tex == NULL) {

		std::cout << "Text Texture Creation Error" << SDL_GetError() << std::endl;
		return NULL;
	}

	//free the surface since only the texture is needed
	SDL_FreeSurface(surface);

	return tex; 

}

void Graphics::ClearBackBuffer()
{
	SDL_RenderClear(mRenderer);
}
void Graphics::DrawTexture(SDL_Texture * tex, SDL_Rect* clip, SDL_Rect* rend)
{
	SDL_RenderCopy(mRenderer, tex, clip, rend);


}
Graphics::Graphics()
{

	// sInitialized variable is going to equal to the Init function
	sInitialized = Init();

}

Graphics::~Graphics()
{
	// Destroys the window created
	SDL_DestroyWindow(sdlWindow);
	// set SDl window to NULL
	sdlWindow = NULL;

	// Destroying renderer and setting it to Null
	SDL_DestroyRenderer(mRenderer);
	mRenderer = NULL;

	TTF_Quit();
	// quit the image
	IMG_Quit();

	// Closing all open SDL graphic libraries
	SDL_Quit();
	IMG_Quit();
}

bool Graphics::Init()
{
	//Initialize SDL everything and handling initialization errors
	if ((SDL_INIT_EVERYTHING | SDL_INIT_AUDIO) < 0 ){ 

		// print a failed message on to the console window
		std::cout << "Initialize SDL - Failed" << SDL_GetError() << std::endl;
		return false;
	}
	
	// create the window
	sdlWindow = SDL_CreateWindow(WINDOW_TITLE, 
											SDL_WINDOWPOS_UNDEFINED, 
											SDL_WINDOWPOS_UNDEFINED, 
											SCREEN_WIDTH,
											SCREEN_HEIGHT, 
											SDL_WINDOW_SHOWN);

	// Handling window creation errors
	if (sdlWindow == NULL) {
		
		std::cout << "Create Window - Failed" << SDL_GetError() << std::endl;
		return false;
	}

	//Creating the renderer
	mRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);

	// Handling renderer creation errors
	if (mRenderer == NULL) {

		std::cout << "Renderer Creation Error " << SDL_GetError() << std::endl;
		return false;
	}

	// Setting the renderers clear color to white
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);

	//Initializing the SDL_image library and handling initialization errors
	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags)) {

		std::cout << "IMG Initialization Error " << IMG_GetError() << std::endl;
		return false;
	}

	if(TTF_Init() == -1) {

		std::cout << "TTF initialization error " << TTF_GetError() << std::endl;
		return false;
	}

	// return true if no errors occurred during initialization
	return true;
}


void Graphics::Render()
{
	SDL_RenderPresent(mRenderer);
}


