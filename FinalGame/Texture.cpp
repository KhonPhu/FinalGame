#include "Texture.h"

Texture::Texture() {
	m_texture = nullptr;

	m_width = 0;
	m_height = 0;
}

bool Texture::LoadImageFromFile(const char* path, SDL_Renderer* renderer) {
	if (m_texture == nullptr) {
		SDL_Surface* loadedSurface = IMG_Load(path);

		if (loadedSurface != nullptr) {
			//std::cout << "Load Texture - success" << std::endl;

			m_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

			if (m_texture != nullptr) {
				//std::cout << "Create texture from surface - success" << std::endl;

				m_width = loadedSurface->w;
				m_height = loadedSurface->h;
			}
			else {
				std::cout << "Create texture from surface - failed" << std::endl;
			}

			SDL_FreeSurface(loadedSurface);
		}
		else {
			std::cout << "Load Texture - failed" << SDL_GetError() << std::endl;
		}
	}
	else {
		std::cout << "Remove the existing texture before loading a texture..." << std::endl;
		return false;
	}

	return m_texture != nullptr;
}

bool Texture::RenderText(const char* text, TTF_Font* font, SDL_Renderer* renderer, SDL_Color color)
{
	// remove the preexisting texture
	ResetTexture();

	// check if the texture is a nullptr
	if (m_texture == nullptr)
	{
		// rendering the text to the surface
		SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, text, color, 500);
		if (textSurface != nullptr)
		{
			//SDL_Log("load text surface - success");
			// converts the rendered text surface to the texture
			m_texture = SDL_CreateTextureFromSurface(renderer, textSurface);
			// if the texture has been loaded successfully
			if (m_texture != nullptr)
			{
				//SDL_Log("convert surface to texture - success");

				// get the width and height of the rendered text
				m_width = textSurface->w;
				m_height = textSurface->h;
			}
			else
			{
				SDL_Log("convert surface to texture - failed: %s", SDL_GetError());
				return false;
			}
			// remove the text surface from the memory
			SDL_FreeSurface(textSurface);
		}
		else {
			SDL_Log("load text surface - failed: %s", TTF_GetError());
			return false;
		}
	}

	return m_texture != nullptr;
}


void Texture::Draw(SDL_Renderer* renderer, int x, int y, SDL_Rect* sourceRect, bool flip) {

	SDL_Rect destRect = { x, y, m_width, m_height };
	SDL_Point center;

	if (sourceRect != nullptr) {
		destRect.w = sourceRect->w;
		destRect.h = sourceRect->h;
	}

	if (!flip) {
		SDL_RenderCopy(renderer, m_texture, sourceRect, &destRect);
	}
	else {
		center.x = destRect.w / 2;
		center.y = destRect.h / 2;
		SDL_RenderCopyEx(renderer, m_texture, sourceRect, &destRect, 0, &center, SDL_FLIP_HORIZONTAL);
	}
}

void Texture::ResetTexture() {
	if (m_texture != nullptr) {
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
}

Texture::~Texture() {
	ResetTexture();
}