// AssetManager.cpp                                                      
// Singleton                                                          
// Used to load all assets used in the game 
#include "AssetManager.h"

//Initializing to NULL
AssetManager* AssetManager::sInstance = NULL;

AssetManager * AssetManager::Instance()
{
	// if instance was not created before
	if (sInstance == NULL)
		// create new instance
		sInstance = new AssetManager();

	// return instance
	return sInstance;
}
void AssetManager::Release()
{
	// delete instance and set it to NULL
	delete sInstance;
	sInstance = NULL;
}


AssetManager::AssetManager()
{

}


AssetManager::~AssetManager()
{
	//Freeing all loaded Textures
	for (auto tex : mTextures) {

		if (tex.second != NULL) {
			// destroy texture
			SDL_DestroyTexture(tex.second);
		}
	}

	mTextures.clear();
}




SDL_Texture * AssetManager::GetTexture(std::string filename)
{
	//Get the full path of the file
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/" + filename);
	
	//If the file has not been already loaded, load it and add it to the mTextures map
	if (mTextures[fullPath] == nullptr)
		mTextures[fullPath] = Graphics::Instance()->LoadTexture(fullPath);

	//returning the cached file from the map
	return mTextures[fullPath];
}
