#include "AudioManager.h"

// Initializing to NULL
AudioManager* AudioManager::sInstance = NULL;

AudioManager* AudioManager::Instance() {

	// Create a new instance if no instance was created before
	if (sInstance == NULL)
		sInstance = new AudioManager();

	return sInstance;
}

void AudioManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

AudioManager::AudioManager()
{
	mAssetMgr = AssetManager::Instance();

	// Initialize the SDL_mixer and handle initialization errors
	if (Mix_OpenAudio(192000, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {

		std::cout << "Mixer Initialization Error:" <<  Mix_GetError() <<std::endl;
	}
}


AudioManager::~AudioManager()
{
	mAssetMgr = NULL;

	// Close the SDL_mixer
	Mix_Quit();
}


void AudioManager::PlayMusic(std::string filename, int loops)
{
	// Play the Mix_Music* loaded in AssetManager so that the file is not reloaded every time
	Mix_PlayMusic(mAssetMgr->GetMusic(filename), loops);
}

void AudioManager::PauseMusic()
{
	if (Mix_PlayingMusic() != 0)
		Mix_PauseMusic();

}

void AudioManager::ResumeMusic()
{
	if (Mix_PausedMusic() != 0)
		Mix_ResumeMusic();
}

void AudioManager::PlaySFX(std::string filename, int loops, int channel)
{
	// Play the Mix_Chunk* loaded in the AssetManager so that the file is not reloaded every time
	Mix_PlayChannel(channel, mAssetMgr->GetSFX(filename), loops);
}
