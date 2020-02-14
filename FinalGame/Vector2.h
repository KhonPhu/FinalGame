#pragma once

#include <math.h>

class Vector2
{
public:
	int x;
	int y;

	Vector2();

	Vector2(float x, float y);

	float Magnitude();
	Vector2 operator+(const Vector2& anotherV);
	Vector2 operator+=(const Vector2& anotherV);
	Vector2 operator-(const Vector2& anotherV);
	Vector2 operator-=(const Vector2& anotherV);
	Vector2 operator*(const float& scalar);
	Vector2 operator*=(const float& scalar);

	void Normalize();
	Vector2 Normalized();

	Vector2 Zero();

	~Vector2();
};

