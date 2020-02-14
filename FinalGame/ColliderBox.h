#pragma once

#include <SDL.h>
#include "Vector2.h"

class ColliderBox
{
public:
	ColliderBox();
	ColliderBox(Vector2 position, int width, int height);
	~ColliderBox();

	// get the position of the bounding box
	const Vector2 GetPosition() const;

	// create a rectangle collision
	bool RectCollision(const ColliderBox& rect);

	// update the ColliderBox
	void Update(Vector2 position);

	// return the width and hright of the bounding box
	const int GetWidth() const;
	const int GetHeight() const;

private:
	Vector2 m_position;
	int m_width;
	int m_height;
	Vector2* zeroVector;
};

