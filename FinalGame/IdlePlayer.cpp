
#include "IdlePlayer.h"


IdlePlayer::IdlePlayer()
{
	m_texture = nullptr;
	m_velocity = zeroVector->Zero();
	m_acceleration = zeroVector->Zero();
	m_maxVelocity = 0.0f;
	m_position = zeroVector->Zero();
	m_sdlRenderer = nullptr;
	m_animation = nullptr;
	m_IdlePlayerSpeed = 0.0f;
	m_IdlePlayerDecceleration = 0.0f;
	m_IdlePlayerDir = 0;
	m_isTouchingGround = false;
	m_collider = new ColliderBox();
	m_audio = new Audio();
}

IdlePlayer::IdlePlayer(SDL_Renderer* renderer, Vector2 pos, int colWidth, int colHeight)
{
	m_velocity = zeroVector->Zero();
	m_acceleration = zeroVector->Zero();
	m_maxVelocity = 1000.0f;
	m_IdlePlayerSpeed = 1000.0f;
	m_IdlePlayerDecceleration = 1000.0f;
	m_IdlePlayerDir = 0;
	m_isTouchingGround = false;
	m_colWidth = colWidth;
	m_colHeight = colHeight;
	m_audio = new Audio();

	// setting the inital IdlePlayer texture
	m_texture = new Texture();
	m_texture->LoadImageFromFile("../assets/PLayerWalking.png", renderer);

	// set the start position and attach the IdlePlayer to the renderer
	m_position = pos;
	m_sdlRenderer = renderer;

	// set up the initial animation
	m_animation = new Animation(m_texture, 4, 0.25f);

	// set up the collider
	m_collider = new ColliderBox(m_position, m_colWidth, m_colHeight);

	std::cout << "IdlePlayer loaded" << std::endl;
}

void IdlePlayer::Draw(SDL_Renderer* renderer)
{
	// Draw the IdlePlayer to the screen
	m_animation->Draw(renderer, m_position.x, m_position.y);

	// Draw a box to visualize the collider 
	SDL_Rect rect = {
		m_collider->GetPosition().x,
		m_collider->GetPosition().y,
		m_collider->GetWidth(),
		m_collider->GetHeight()
	};

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderDrawRect(renderer, &rect);
}

void IdlePlayer::Update(float deltaTime)
{
	m_velocity += m_acceleration * deltaTime;

	float length = m_velocity.Magnitude();
	if (length >= m_maxVelocity) {
		m_velocity.Normalize();
		m_velocity = m_velocity * m_maxVelocity;
	}

	m_position += m_velocity * deltaTime;

	if (!m_isTouchingGround) {
		// Apply fake gravity
		m_position.y += 1000.0f * deltaTime;
	}

	m_acceleration = zeroVector->Zero();

	m_collider->Update(m_position);

	m_animation->Update(deltaTime);
}

void IdlePlayer::HandleInputS(Input* input)
{
	// Change IdlePlayer Direction when holding a key down
	if (input->isKeyDown(SDL_SCANCODE_SPACE)) {
		m_IdlePlayerDir = 1;
		m_audio->PlaySFX("../assets/Attack.wav");
		AddForce(Vector2(2, 0) * m_IdlePlayerSpeed);
	}
	// if we let go of the Space key
	if (input->isKeyUp(SDL_SCANCODE_SPACE)) {
		// check if we are still moving space
		if (m_velocity.x > 0) {
			// if so, slow down
			Deccelerate(Vector2(2, 0) * m_IdlePlayerDecceleration);
		}
	}

	// Change IdlePlayer Direction when holding a key down
	if (input->isKeyDown(SDL_SCANCODE_RETURN)) {
		
	}
	// if we let go of the ENter key
	if (input->isKeyUp(SDL_SCANCODE_RETURN)) {
		
	}

	// if we are not moving the IdlePlayer in a direction
	if (input->isKeyUp(SDL_SCANCODE_SPACE)) {
		// set IdlePlayer direction to idle
		m_IdlePlayerDir = 0;
	}

	AnimationLogic(input);
}

void IdlePlayer::AnimationLogic(Input* input)
{
	// Pressed d key
	if (input->wasKeyPressed(SDLK_SPACE)) {
		IdleAnimation();
		// clear the d key state
		input->SetKeyboardStatesFalse(SDLK_SPACE);
	}


	if (input->wasKeyReleased(SDLK_SPACE) && m_IdlePlayerDir == 2) {
		IdleAnimation();
		// clear the d key state
		input->SetKeyboardStatesFalse(SDLK_SPACE);
	}


	if (input->wasKeyReleased(SDLK_SPACE) && m_IdlePlayerDir == 0) {
		IdleAnimation();
		input->SetKeyboardStatesFalse(SDLK_SPACE);
	}
}

void IdlePlayer::IdleAnimation()
{
	// Reset the texture
	m_texture->ResetTexture();
	// Load the animation
	m_texture->LoadImageFromFile("../assets/PlayerWalking.png", m_sdlRenderer);
	// play the animation
	m_animation = new Animation(m_texture, 4, 0.25f);
}


void IdlePlayer::AddForce(Vector2 force)
{
	m_acceleration += force;
}

void IdlePlayer::Deccelerate(Vector2 force)
{
	m_acceleration -= force;
}

ColliderBox* IdlePlayer::GetCollider()
{
	return m_collider;
}

void IdlePlayer::ToggleGround(bool toggle)
{
	// Toggle isTouchingGround
	m_isTouchingGround = toggle;
}

Vector2 IdlePlayer::GetIdlePlayerPosition()
{
	return m_position;
}

void IdlePlayer::ChangeIdlePlayerPos(Vector2 pos)
{
	m_position = pos;
}


IdlePlayer::~IdlePlayer()
{
}
