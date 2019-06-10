// AssetManager.h                                                      
// Singleton                                                          
// Used to load all assets used in the game                      
#ifndef _ASSETMANAGER_
#define _ASSETMANAGER_
#include "Graphics.h"
#include <SDL_mixer.h>
#include <map>


class AssetManager
{
private: 
	//Needed to make AssetManager a singleton class
	static AssetManager* sInstance;
	//Used to cache all loaded images
	std::map<std::string, SDL_Texture*> mTextures;
	//Used to cache all loaded music files
	std::map<std::string, Mix_Music*> mMusic;
	//Used to cache all loaded sound effect files
	std::map<std::string, Mix_Chunk*> mSFX;
	//Used to cache all rendered text converted to textures
	std::map<std::string, SDL_Texture*> mText;
	//Used to cache all loaded fonts
	std::map<std::string, TTF_Font*> mFonts;


	TTF_Font* GetFont(std::string filename, int size);

	AssetManager();
	~AssetManager();

public:
	//Returns a pointer to the class instance  
	static AssetManager* Instance();
	//Releases the class instance and sets it back to NULL 
	static void Release();

	//Should be used when any texture needs to be loaded from file
	//If the texture was not previously loaded, it is loaded from file then cached are returned
	//otherwise, the already cached texture is returned
	SDL_Texture* GetTexture(std::string filename);

	//If the given text with the same font and size and color was renderer previously, the cached texture is returned
	//If it has not been rendered before, the text is rendered and cached, then returned to be reused again later
	//-------------------------------------------------------------------------------------------------------------------
	SDL_Texture* GetText(std::string text, std::string filename, int size, SDL_Color color);

	//------------------------------------------------------------------------------------------
	//If the music file was opened before, the cached Mix_Music* is returned
	//otherwise, the file is loaded and converted into a Mix_Music* and cached then returned
	//------------------------------------------------------------------------------------------
	Mix_Music* GetMusic(std::string filename);

	//------------------------------------------------------------------------------------------
	//If the SFX file was opened before, the cached Mix_Chunk* is returned
	//otherwise, the file is loaded and converted into a Mix_Chunk* and cached then returned
	//------------------------------------------------------------------------------------------
	Mix_Chunk* GetSFX(std::string filename);

	
};

#endif