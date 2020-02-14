#include "IdleObject.h"

class IdlePlayer : public IdleObject
{
public:
	IdlePlayer();
	IdlePlayer(SDL_Renderer* renderer, Vector2 pos, int colWidth, int colHeight);

	void Draw(SDL_Renderer* renderer) override;
	void Update(float deltaTime) override;
	void HandleInputS(Input* input) override;

	void AnimationLogic(Input* input);

	// Animtion Functions
	void IdleAnimation();
	void RunAnimation(bool flip = false);
	void RunUpDown(bool flip = false);

	void AddForce(Vector2 force);
	void Deccelerate(Vector2 force);

	ColliderBox* GetCollider();

	void ToggleGround(bool toggle);

	Vector2 GetIdlePlayerPosition();
	void ChangeIdlePlayerPos(Vector2 pos);

	~IdlePlayer();

private:
	SDL_Renderer* m_sdlRenderer;
	Animation* m_animation;
	Vector2 m_acceleration;
	Vector2 m_velocity;
	float m_maxVelocity;
	Audio* m_audio;

	// Collider
	ColliderBox* m_collider;
	int m_colWidth;
	int m_colHeight;

	float m_IdlePlayerSpeed;
	float m_IdlePlayerDecceleration;
	int m_IdlePlayerDir;
	bool m_isTouchingGround;

	Vector2* zeroVector;
};
