#pragma once
#include <iostream>
#include <cmath>

const float Pi = 3.14159;


struct Vector2
{
	float x, y;

	Vector2(float, float);
	//Конструктор и Деструктор
	Vector2(); 

	~Vector2();
	//Произведение и деление на число
	Vector2 operator*(float) const;
	
	Vector2 operator/(float) const;

	//Классические операторы
	Vector2 operator+(const Vector2&) const;
	
	Vector2& operator+=(const Vector2& );

	Vector2& operator-=(const Vector2& );

	Vector2 operator-(const Vector2& ) const;
	//Векторное произведение
	float operator^(const Vector2&) const;
	//Скалярное произведение
	float operator*(const Vector2& ) const;
	//Длина вектора
	float Len() const;
	//Квадрат длины
	float SquareLen() const;
	//Единичный вектор
	Vector2 Norm();
	//Перпандикуляр
	Vector2 Perp();
	//Повороты
	Vector2& Rotate(float);
	
	Vector2 GetRotated(float);
};

std::istream& operator>>(std::istream&, Vector2&);
std::ostream& operator<<(std::ostream&, const Vector2&);

