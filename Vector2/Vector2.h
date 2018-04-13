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
	
	// fixit: ой, вверх ногами операторы << и >> получились
	// вынесите эти два метода наружу из структуры -> обычные ф-и 
	// std::ostream& operator<<(std::ostream&, const Vector2& v);
	// std::istream& operator>>(std::istream&, Vector2& v)
	std::ostream& operator<<(std::ostream&);

	std::istream& operator>>(std::istream&);
	
	Vector2& operator+=(const Vector2& );

	Vector2& operator-=(const Vector2& );

	Vector2 operator-(const Vector2& ) const;

	float operator^(const Vector2&) const;

	float operator*(const Vector2& ) const;

	// fixit: названия методов должны быть в одном стиле ... возможно len и squareLen
	// лишь бы везде одинаково
	float Len() const;
	
	float SquareLen() const;
	
	// fixit: посмотрите, как у вас сделаны rotate и getRotated. видимо norm и perp надо в том же стиле сделать
	Vector2 norm();
	Vector2 perp();
	
	Vector2& rotate(float);
	
	// fixit: если вы возвращаете Vector2, то метод должен быть константный. Если Vector2& , то неконстантный
	Vector2 getRotated(float);

};
