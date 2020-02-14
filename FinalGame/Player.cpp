
#include "Player.h"


Player::Player()
{
	m_texture = nullptr;
	m_velocity = zeroVector->Zero();
	m_acceleration = zeroVector->Zero();
	m_maxVelocity = 0.0f;
	m_position = zeroVector->Zero();
	m_sdlRenderer = nullptr;
	m_animation = nullptr;
	m_playerSpeed = 0.0f;
	m_playerDecceleration = 0.0f;
	m_playerDir = 0;
	m_isTouchingGround = false;
	m_collider = new ColliderBox();
	m_audio = new Audio();
}

Player::Player(SDL_Renderer* renderer, Vector2 pos, int colWidth, int colHeight)
{
	m_velocity = zeroVector->Zero();
	m_acceleration = zeroVector->Zero();
	m_maxVelocity = 500.0f;
	m_playerSpeed = 500.0f;
	m_playerDecceleration = 500.0f;
	m_playerDir = 0;
	m_isTouchingGround = false;
	m_colWidth = colWidth;
	m_colHeight = colHeight;
	m_audio = new Audio();

	// setting the inital player texture
	m_texture = new Texture();
	m_texture->LoadImageFromFile("../assets/PlayerIdle.png", renderer);

	// set the start position and attach the player to the renderer
	m_position = pos;
	m_sdlRenderer = renderer;

	// set up the initial animation
	m_animation = new Animation(m_texture, 4, 0.25f);

	// set up the collider
	m_collider = new ColliderBox(m_position, m_colWidth, m_colHeight);

	std::cout << "Player loaded" << std::endl;
}

void Player::Draw(SDL_Renderer* renderer)
{
	// Draw the player to the screen
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

void Player::Update(float deltaTime)
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

void Player::HandleInput(Input* input)
{
	// Change Player Direction when holding a key down
	if (input->isKeyDown(SDL_SCANCODE_D)) {
		m_playerDir = 1;
		m_audio->PlaySFX("../assets/playerwalk.wav");
		AddForce(Vector2(2, 0) * m_playerSpeed);
	}
	// if we let go of the d key
	if (input->isKeyUp(SDL_SCANCODE_D)) {
		// check if we are still moving right
		if (m_velocity.x > 0) {
			// if so, slow down
			Deccelerate(Vector2(2, 0) * m_playerDecceleration);
		}
	}

	if (input->isKeyDown(SDL_SCANCODE_A)) {
		m_playerDir = 2;
		m_audio->PlaySFX("../assets/playerwalk.wav");
		AddForce(Vector2(-2, 0) * m_playerSpeed);
	}
	// if we let go of the a key
	if (input->isKeyUp(SDL_SCANCODE_A)) {
		// check if we are still moving left
		if (m_velocity.x < 0) {
			// if so, slow down
			Deccelerate(Vector2(-2, 0) * m_playerDecceleration);
		}
	}

	if (input->isKeyDown(SDL_SCANCODE_W)) {
		m_playerDir = 3;
		m_audio->PlaySFX("../assets/playerwalk.wav");
		AddForce(Vector2(0, -2) * m_playerSpeed);
	}
	// if we let go of the w key
	if (input->isKeyUp(SDL_SCANCODE_W)) {
		// check if we are still moving up
		if (m_velocity.y < 0) {
			// if so, slow down
			Deccelerate(Vector2(0, -2) * m_playerDecceleration);
		}
	}

	if (input->isKeyDown(SDL_SCANCODE_S)) {
		m_playerDir = 4;
		m_audio->PlaySFX("../assets/playerwalk.wav");
		AddForce(Vector2(0, 2) * m_playerSpeed);
	}
	// if we let go of the s key
	if (input->isKeyUp(SDL_SCANCODE_S)) {
		// check if we are still moving down
		if (m_velocity.y > 0) {
			// if so, slow down
			Deccelerate(Vector2(0, 2) * m_playerDecceleration);
		}
	}


	// if we are not moving the player in a direction
	if (input->isKeyUp(SDL_SCANCODE_A) && input->isKeyUp(SDL_SCANCODE_D) && input->isKeyUp(SDL_SCANCODE_W) && input->isKeyUp(SDL_SCANCODE_S)) {
		// set player direction to idle
		m_playerDir = 0;
	}

	AnimationLogic(input);
}

void Player::AnimationLogic(Input* input)
{
	// Pressed d key
	if (input->wasKeyPressed(SDLK_d)) {
		RunAnimation();
		// clear the d key state
		input->SetKeyboardStatesFalse(SDLK_d);
	}

	if (input->wasKeyPressed(SDLK_a)) {
		RunAnimation(true);
		// clear the a key state
		input->SetKeyboardStatesFalse(SDLK_a);
	}

	if (input->wasKeyPressed(SDLK_w)) {
		RunUpDown(true);
		// clear the a key state
		input->SetKeyboardStatesFalse(SDLK_w);
	}

	if (input->wasKeyPressed(SDLK_s)) {
		IdleAnimation();
		// clear the a key state
		input->SetKeyboardStatesFalse(SDLK_s);
	}

	if (input->wasKeyReleased(SDLK_d) && m_playerDir == 2) {
		IdleAnimation();
		// clear the d key state
		input->SetKeyboardStatesFalse(SDLK_d);
	}

	if (input->wasKeyReleased(SDLK_a) && m_playerDir == 1) {
		IdleAnimation();
		// clear the a key state
		input->SetKeyboardStatesFalse(SDLK_a);
	}

	if (input->wasKeyReleased(SDLK_w) && m_playerDir == 3) {
		IdleAnimation();
		input->SetKeyboardStatesFalse(SDLK_w);
	}

	if (input->wasKeyReleased(SDLK_s) && m_playerDir == 4) {
		IdleAnimation();
		input->SetKeyboardStatesFalse(SDLK_s);
	}

	if (input->wasKeyReleased(SDLK_d) && m_playerDir == 0) {
		IdleAnimation();
		input->SetKeyboardStatesFalse(SDLK_a);
		input->SetKeyboardStatesFalse(SDLK_d);
		input->SetKeyboardStatesFalse(SDLK_w);
		input->SetKeyboardStatesFalse(SDLK_s);
	}
	if (input->wasKeyReleased(SDLK_a) && m_playerDir == 0) {
		IdleAnimation();
		input->SetKeyboardStatesFalse(SDLK_a);
		input->SetKeyboardStatesFalse(SDLK_d);
		input->SetKeyboardStatesFalse(SDLK_w);
		input->SetKeyboardStatesFalse(SDLK_s);
	}
	if (input->wasKeyReleased(SDLK_w) && m_playerDir == 0) {
		IdleAnimation();
		input->SetKeyboardStatesFalse(SDLK_a);
		input->SetKeyboardStatesFalse(SDLK_d);
		input->SetKeyboardStatesFalse(SDLK_w);
		input->SetKeyboardStatesFalse(SDLK_s);
	}
	if (input->wasKeyReleased(SDLK_s) && m_playerDir == 0) {
		IdleAnimation();
		input->SetKeyboardStatesFalse(SDLK_a);
		input->SetKeyboardStatesFalse(SDLK_d);
		input->SetKeyboardStatesFalse(SDLK_w);
		input->SetKeyboardStatesFalse(SDLK_s);
	}
}

void Player::IdleAnimation()
{
	// Reset the texture
	m_texture->ResetTexture();
	// Load the animation
	m_texture->LoadImageFromFile("../assets/PlayerIdle.png", m_sdlRenderer);
	// play the animation
	m_animation = new Animation(m_texture, 4, 0.25f);
}

void Player::RunAnimation(bool flip)
{
	// Reset the texture
	m_texture->ResetTexture();
	// Load the animation
	m_texture->LoadImageFromFile("../assets/PlayerWalking.png", m_sdlRenderer);
	// play the animation
	m_animation = new Animation(m_texture, 4, 0.125f, flip);
}

void Player::RunUpDown(bool flip)
{
	// Reset the texture
	m_texture->ResetTexture();
	// Load the animation
	m_texture->LoadImageFromFile("../assets/PlayerUpDown.png", m_sdlRenderer);
	// play the animation
	m_animation = new Animation(m_texture, 4, 0.125f, flip);

}

void Player::AddForce(Vector2 force)
{
	m_acceleration += force;
}

void Player::Deccelerate(Vector2 force)
{
	m_acceleration -= force;
}

ColliderBox* Player::GetCollider()
{
	return m_collider;
}

void Player::ToggleGround(bool toggle)
{
	// Toggle isTouchingGround
	m_isTouchingGround = toggle;
}

Vector2 Player::GetPlayerPosition()
{
	return m_position;
}

void Player::ChangePlayerPos(Vector2 pos)
{
	m_position = pos;
}


Player::~Player()
{
}
