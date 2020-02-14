#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Texture
{
public:
	Texture();

	bool LoadImageFromFile(const char* path, SDL_Renderer* renderer);

	void Draw(SDL_Renderer* renderer, int x, int y, SDL_Rect* sourceRect = NULL, bool flip = false);

	int GetImageWidth() { return m_width; }
	int GetImageHeight() { return m_height; }

	void ResetTexture();

	bool RenderText(const char* text, TTF_Font* font, SDL_Renderer* renderer, SDL_Color color);

	~Texture();
private:
	// hardware accelerated texture rendering
	SDL_Texture* m_texture;

	// texture dimensions
	int m_width;
	int m_height;
};

