#pragma once
#include "IdleObject.h"

class HealthBarEnemy : public IdleObject
{
public:
	HealthBarEnemy();
	HealthBarEnemy(SDL_Renderer* renderer, Vector2 pos, int colWidth, int colHeight);

	virtual void Draw(SDL_Renderer* renderer);
	virtual void Update(float deltaTime);
	virtual void HandleInput(float delatTime);

	ColliderBox* GetCollider();

	Vector2 GetPlayerPosition();

	~HealthBarEnemy();

private:
	SDL_Renderer* m_sdlRenderer;
	Animation* m_animation;

	// Collider
	ColliderBox* m_collider;
	int m_colWidth;
	int m_colHeight;

	Vector2 zeroVector;
};

