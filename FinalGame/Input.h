#pragma once

#include <SDL.h>

class Input
{
public:
	Input();

	void UpdateInput();

	// A key is in down or up state
	bool isKeyDown(SDL_Scancode key);
	bool isKeyUp(SDL_Scancode key);

	// Key has been pressed
	bool wasKeyPressed(SDL_Keycode key);
	// Key has been released
	bool wasKeyReleased(SDL_Keycode key);
	// Set was to false
	void SetKeyboardStatesFalse(SDL_Keycode key);

	bool GetGameOver();
	void ToggleGameOver();

	~Input();

private:

	// To return if we've exited the game through input
	bool isGameOver;

	const Uint8* m_keyboardState;
	// Store each keys press state
	int m_keyboardPressState[322];
};

