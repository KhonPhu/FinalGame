#include "ColliderBox.h"

ColliderBox::ColliderBox()
{
	m_position = zeroVector->Zero();
	m_width = 0;
	m_height = 0;
}

ColliderBox::ColliderBox(Vector2 position, int width, int height)
{
	m_position = position;
	m_width = width;
	m_height = height;
}

ColliderBox::~ColliderBox() {}

const Vector2 ColliderBox::GetPosition() const
{
	return m_position;
}

bool ColliderBox::RectCollision(const ColliderBox& rect)
{
	if (
		rect.GetPosition().x + rect.GetWidth() < m_position.x ||
		rect.GetPosition().x > m_width + m_position.x ||
		rect.GetPosition().y + rect.GetHeight() < m_position.y ||
		rect.GetPosition().y > m_height + m_position.y
		) {
		return false;
	}
	return true;
}

void ColliderBox::Update(Vector2 position)
{
	m_position = position;
}

const int ColliderBox::GetWidth() const
{
	return m_width;
}

const int ColliderBox::GetHeight() const
{
	return m_height;
}
