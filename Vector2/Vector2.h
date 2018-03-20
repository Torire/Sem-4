#pragma once
inline
#include <iostream>
#include <cmath>

const float Pi = 3.14159;

struct Vector2
{
	float x, y;

	Vector2(float, float);

	Vector2(); 

	~Vector2();

	Vector2 operator+(const Vector2&) const;

	Vector2 operator*(float) const;
	
	Vector2 operator/(float) const;
	
	std::ostream& operator<<(std::ostream&);

	std::istream& operator>>(std::istream&);
	
	Vector2& operator+=(const Vector2& );

	Vector2& operator-=(const Vector2& );

	Vector2 operator-(const Vector2& ) const;

	float operator^(const Vector2&) const;

	float operator*(const Vector2& ) const;

	float Len() const;
	
	float SquareLen() const;
	
	Vector2 norm();
	
	Vector2 perp();
	
	Vector2& rotate(float);
	
	Vector2 getRotated(float);

};
