#ifndef _AUDIOMANAGER_H
#define _AUDIOMANAGER_H

#include "AssetManager.h"

class AudioManager
{
private:
	// Constructor is private so that Instance() must be used to get an instance when needed
	AudioManager();
	// Destructor is private so that the instance can only be destroyed using Release()
	~AudioManager();

	// Needed to make AudioManager a singleton class
	static AudioManager* sInstance;

	// Used to load audio files
	AssetManager* mAssetMgr;

public:

	// Returns a pointer to the class instance
	static AudioManager* Instance();

	// Realeses the class instance and sets it back to NULL
	static void Release();

	// Sets the BGM to play using the provided files
	void PlayMusic(std::string filename, int loops = -1);

	// Pauses the currently playing BGM if there is any
	void PauseMusic();

	// Resume paused BGM
	void ResumeMusic();

	// Plays sound effect from file provided
	void PlaySFX(std::string filename, int loops = 0, int channel = 0);

};

#endif