#include "Vector2.h"
//Конструкторы
	Vector2::Vector2()
	{
	x = 0;
	y = 0;
	}

	Vector2::Vector2(float kx, float ky)
	{
		x = kx;
		y = ky;
	}

	//Деструктор
	Vector2::~Vector2(){}

	Vector2 Vector2::operator+(const Vector2& other) const
	{
		Vector2 result;
		result.x = x + other.x;
		result.y = y + other.y;
		return result;
	}
	//Умножение, деление координат на число
	Vector2 Vector2::operator*(float k) const
	{
		return Vector2(x * k, y * k);
	}

	Vector2 Vector2::operator/(float k) const
	{
		return Vector2(x / k, y / k);
	}

	//Ввод и вывод
	std::ostream& Vector2::operator<<(std::ostream& stream)
	{
		stream << x << " " << y;
		return stream;
	}

	std::istream& Vector2::operator>>(std::istream& stream)
	{
		stream >> x >> y;
		return stream;
	}

	Vector2& Vector2::operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2 Vector2::operator-(const Vector2& other) const
	{
		Vector2 result;
		result.x = x - other.x;
		result.y = y - other.y;
		return result;
	}
	//Векторное произведение
	float Vector2::operator^(const Vector2& other) const
	{
		return x * other.y - y * other.x; 
	}
	//Скалярное произведение
	float Vector2::operator*(const Vector2& other) const
	{
		return x * other.x + y * other.y;
	}
	//Длина вектора
	float Vector2::Len() const
	{
		return sqrt(x * x + y * y);
	}
	//Квадрат длины
	float Vector2::SquareLen() const
	{
		return x * x + y * y;
	}
	//Единичный вектор
	Vector2 Vector2::norm()
	{
		Vector2 result;
		result.x = x / Len();
		result.y = y / Len();
		return result;
	}
	//Перпендикуляр
	Vector2 Vector2::perp()
	{
		Vector2 result;
		result.x = y;
		result.y = -x;
		return result;
	}
	//Повороты
	Vector2& Vector2::rotate(float deg)
	{
		float deg0 = atan2f (y,x);
		x = Len() *  cos ( deg0 + deg);  
		y =  Len() * sin ( deg0 + deg);
		return *this;
	}	
	
	Vector2 Vector2::getRotated(float deg)
	{
		Vector2 result;
		float deg0 = atan2f (y,x);
		result.x = Len() *  cos ( deg0 + deg / 180 * Pi);  
		result.y =  Len() * sin ( deg0 + deg / 180 * Pi);
		return result;
	}	

	
	
	
