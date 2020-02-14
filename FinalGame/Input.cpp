#include "Input.h"

Input::Input() {
	isGameOver = false;

}

void Input::UpdateInput() {
	SDL_Event e;
	if (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			isGameOver = true;
			break;
		case SDL_KEYDOWN:
			// Will exit game when escape is pressed
			if (e.button.button == SDL_SCANCODE_ESCAPE) {
				isGameOver = true;
			}
			m_keyboardState = SDL_GetKeyboardState(NULL);

			// Making sure we only change the int once per button press
			if (e.key.repeat == 0) {
				m_keyboardPressState[e.key.keysym.sym] = 1;
			}
			break;
		case SDL_KEYUP:
			m_keyboardState = SDL_GetKeyboardState(NULL);
			m_keyboardPressState[e.key.keysym.sym] = 2;
			break;
		default:
			break;
		}
	}
}


bool Input::isKeyDown(SDL_Scancode key)
{
	if (m_keyboardState != nullptr) {
		if (m_keyboardState[key]) {
			return true;
		}
	}
	return false;
}

bool Input::isKeyUp(SDL_Scancode key)
{
	if (m_keyboardState != nullptr) {
		if (m_keyboardState[key]) {
			return false;
		}
	}
	return true;
}

bool Input::wasKeyPressed(SDL_Keycode key)
{
	if (m_keyboardPressState[key] == 1) {
		return true;
	}
	return false;
}

bool Input::wasKeyReleased(SDL_Keycode key)
{
	if (m_keyboardPressState[key] == 2) {
		return true;
	}
	return false;
}

void Input::SetKeyboardStatesFalse(SDL_Keycode key)
{
	m_keyboardPressState[key] = 0;
}

bool Input::GetGameOver()
{
	return isGameOver;
}

void Input::ToggleGameOver()
{
	isGameOver = true;
}


Input::~Input() {

}