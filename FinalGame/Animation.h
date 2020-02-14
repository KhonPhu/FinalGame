#pragma once

#include "Texture.h"

class Animation
{
public:
	Animation();

	Animation(Texture* spriteSheet, int numberOfFrames, float framesDuration, bool flip = false);

	void Update(float deltaTime);

	void Draw(SDL_Renderer* renderer, int x, int y);

	~Animation();

private:
	// get the number of frames in the spritesheet
	int m_numberOfFrames;

	// width of each frame
	int m_frameWidth;
	// height of each frame
	int m_frameHeight;

	// delay between each frame
	float m_frameDuration;

	// store the spritesheet
	Texture* m_spriteSheet;

	// timer for each frame
	float m_frameTimer;

	// current frame 
	int m_currentFrame;

	// check if the texture is reversed
	bool m_flip;
};

