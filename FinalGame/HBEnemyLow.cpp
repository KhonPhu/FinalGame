#include "HBEnemyLow.h"

HBEnemyLow::HBEnemyLow()
{
	m_position = zeroVector.Zero();
	m_texture = nullptr;
	m_sdlRenderer = nullptr;
	m_animation = nullptr;
	m_collider = nullptr;
	m_colWidth = 0;
	m_colHeight = 0;
}

HBEnemyLow::HBEnemyLow(SDL_Renderer* renderer, Vector2 pos, int colWidth, int colHeight)
{
	m_position = pos;
	m_colWidth = colWidth;
	m_colHeight = colHeight;


	// setting the inital player texture
	m_texture = new Texture();
	m_texture->LoadImageFromFile("../assets/HealthBar_Low.png", renderer);

	// set the start position and attach the player to the renderer
	m_position = pos;
	m_sdlRenderer = renderer;

	// set up the initial animation
	m_animation = new Animation(m_texture, 1, 0.5f);

	// set up the collider
	m_collider = new ColliderBox(m_position, m_colWidth, m_colHeight);

	std::cout << "Health Bar Enemy loaded" << std::endl;

}

void HBEnemyLow::Draw(SDL_Renderer* renderer)
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

void HBEnemyLow::Update(float deltaTime)
{
	m_collider->Update(m_position);
	m_animation->Update(deltaTime);
}

void HBEnemyLow::HandleInput(float delatTime)
{

}

ColliderBox* HBEnemyLow::GetCollider()
{
	return m_collider;
}



HBEnemyLow::~HBEnemyLow()
{
	if (m_texture != nullptr) {
		delete m_texture;
		m_texture = nullptr;
	}
}
