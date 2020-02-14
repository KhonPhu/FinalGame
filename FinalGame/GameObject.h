#pragma once

#include "Texture.h"
#include "Input.h"
#include "Vector2.h"
#include "Animation.h"
#include "ColliderBox.h"
#include "Audio.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void Draw(SDL_Renderer* reneder);
	virtual void Update(float deltaTime);
	virtual void HandleInput(Input* input);

protected:
	Vector2 m_position;
	Texture* m_texture;
};

