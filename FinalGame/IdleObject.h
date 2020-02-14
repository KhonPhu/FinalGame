#pragma once

#include "Texture.h"
#include "Input.h"
#include "Vector2.h"
#include "Animation.h"
#include "ColliderBox.h"
#include "Audio.h"

class IdleObject
{
public:
	IdleObject();
	~IdleObject();

	virtual void Draw(SDL_Renderer* reneder);
	virtual void Update(float deltaTime);
	virtual void HandleInputS(Input* input);

protected:
	Vector2 m_position;
	Texture* m_texture;
};

