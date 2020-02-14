#include "Animation.h"

Animation::Animation()
{
	m_currentFrame = 0;
	m_frameDuration = 0.0f;
	m_frameTimer = 0.0f;
	m_flip = false;
}

Animation::Animation(Texture* spriteSheet, int numberOfFrames, float framesDuration, bool flip)
{
	m_spriteSheet = spriteSheet;
	m_numberOfFrames = numberOfFrames;
	m_frameDuration = framesDuration;
	m_frameTimer = 0.0f;
	m_currentFrame = 0;
	m_flip = flip;
	if (m_spriteSheet != nullptr) {
		m_frameWidth = m_spriteSheet->GetImageWidth() / m_numberOfFrames;
		m_frameHeight = m_spriteSheet->GetImageHeight();
	}
}

void Animation::Update(float deltaTime)
{
	m_frameTimer += deltaTime;

	if (m_frameTimer >= m_frameDuration) {
		m_currentFrame++;
		m_frameTimer = 0.0f;

		// have we reached our final frame?
		if (m_currentFrame >= m_numberOfFrames) {
			// go back to 0
			m_currentFrame = 0;
		}
	}
}

void Animation::Draw(SDL_Renderer* renderer, int x, int y)
{
	// clip the spritesheet to one frame
	SDL_Rect clip;

	clip.x = m_currentFrame * m_frameWidth;
	clip.y = 0;
	clip.w = m_frameWidth;
	clip.h = m_frameHeight;

	// Draw the frame we've clipped
	m_spriteSheet->Draw(renderer, x, y, &clip, m_flip);
}

Animation::~Animation()
{
	if (m_spriteSheet != nullptr) {
		delete m_spriteSheet;
		m_spriteSheet = nullptr;
	}
}
