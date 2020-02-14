#include "Audio.h"

Audio::Audio()
{
	m_bgAudio = nullptr;
	m_sfx = nullptr;
}

void Audio::PlayBGMusic(const char* path)
{
	m_bgAudio = Mix_LoadMUS(path);

	if (m_bgAudio != nullptr) {
		if (Mix_PlayingMusic() == 0) {
			if (Mix_PlayMusic(m_bgAudio, 0) == -1) {
				std::cout << "Load Background Music - failed: " << SDL_GetError() << std::endl;
			}
			else {
				Mix_VolumeMusic(10);
			}
		}
	}
}

void Audio::PlaySFX(const char* path)
{
	m_sfx = Mix_LoadWAV(path);

	if (m_sfx != nullptr) {
		if (Mix_Playing(2) == 0) {
			Mix_VolumeChunk(m_sfx, 10);
			Mix_PlayChannel(-1, m_sfx, 0);
		}
	}
}

Audio::~Audio()
{
}
