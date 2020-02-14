#include "Wall_2.h"

Wall_2::Wall_2()
{
	m_position = zeroVector.Zero();
	m_texture = nullptr;
	m_sdlRenderer = nullptr;
	m_animation = nullptr;
	m_collider = nullptr;
	m_colWidth = 0;
	m_colHeight = 0;
}

Wall_2::Wall_2(SDL_Renderer* renderer, Vector2 pos, int colWidth, int colHeight)
{
	m_position = pos;
	m_colWidth = colWidth;
	m_colHeight = colHeight;


	// setting the inital player texture
	m_texture = new Texture();
	m_texture->LoadImageFromFile("../assets/wall_y.png", renderer);

	// set the start position and attach the player to the renderer
	m_position = pos;
	m_sdlRenderer = renderer;

	// set up the initial animation
	m_animation = new Animation(m_texture, 1, 0.1f);

	// set up the collider
	m_collider = new ColliderBox(m_position, m_colWidth, m_colHeight);

}

void Wall_2::Draw(SDL_Renderer* renderer)
{
	m_animation->Draw(renderer, m_position.x, m_position.y);

	// Draw a box to visualize the collider and make it blue
	SDL_Rect rect = {
		m_collider->GetPosition().x,
		m_collider->GetPosition().y,
		m_collider->GetWidth(),
		m_collider->GetHeight()
	};

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &rect);
}

void Wall_2::Update(float deltaTime)
{
	m_collider->Update(m_position);
	m_animation->Update(deltaTime);
}

void Wall_2::HandleInput(float delatTime)
{

}

ColliderBox* Wall_2::GetCollider()
{
	return m_collider;
}



Wall_2::~Wall_2()
{
	if (m_texture != nullptr) {
		delete m_texture;
		m_texture = nullptr;
	}
}
