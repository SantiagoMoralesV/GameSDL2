// AssetManager.h                                                      
// Singleton                                                          
// Used to load all assets used in the game                      
#ifndef _ASSETMANAGER_
#define _ASSETMANAGER_
#include "Graphics.h"
#include <map>


class AssetManager
{
private:
	//Needed to make AssetManager a singleton class
	static AssetManager* sInstance;
	//Used to cache all loaded images
	std::map<std::string, SDL_Texture*> mTextures;

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

	
};

#endif