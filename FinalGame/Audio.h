#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
class Audio
{
public:
	Audio();

	void PlayBGMusic(const char* path);
	void PlaySFX(const char* path);

	~Audio();

private:
	Mix_Music* m_bgAudio;
	Mix_Chunk* m_sfx;
};

