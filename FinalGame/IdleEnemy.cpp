#include "IdleEnemy.h"

IdleEnemy::IdleEnemy()
{
	m_position = zeroVector.Zero();
	m_texture = nullptr;
	m_sdlRenderer = nullptr;
	m_animation = nullptr;
	m_collider = nullptr;
	m_colWidth = 0;
	m_colHeight = 0;
}

IdleEnemy::IdleEnemy(SDL_Renderer* renderer, Vector2 pos, int colWidth, int colHeight)
{
	m_position = pos;
	m_colWidth = colWidth;
	m_colHeight = colHeight;


	// setting the inital player texture
	m_texture = new Texture();
	m_texture->LoadImageFromFile("../assets/EnemyWalking.png", renderer);

	// set the start position and attach the player to the renderer
	m_position = pos;
	m_sdlRenderer = renderer;

	// set up the initial animation
	m_animation = new Animation(m_texture, 5, 0.5f);

	// set up the collider
	m_collider = new ColliderBox(m_position, m_colWidth, m_colHeight);

	std::cout << "idle Enemy loaded" << std::endl;

}

void IdleEnemy::Draw(SDL_Renderer* renderer)
{
	m_animation->Draw(renderer, m_position.x, m_position.y);

	// Draw a box to visualize the collider and make it blue
	SDL_Rect rect = {
		m_collider->GetPosition().x,
		m_collider->GetPosition().y,
		m_collider->GetWidth(),
		m_collider->GetHeight()
	};

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderDrawRect(renderer, &rect);
}

void IdleEnemy::Update(float deltaTime)
{
	m_collider->Update(m_position);
	m_animation->Update(deltaTime);
}

void IdleEnemy::HandleInputS(float delatTime)
{

}

ColliderBox* IdleEnemy::GetCollider()
{
	return m_collider;
}



IdleEnemy::~IdleEnemy()
{
	if (m_texture != nullptr) {
		delete m_texture;
		m_texture = nullptr;
	}
}
