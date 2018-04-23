#include "Vector2.h"

/*
лучше использовать списки инициализации, если есть возможность
Vector2::Vector2() : x(0), y(0)
{
} (done?)
*/
Vector2::Vector2() : x(0), y(0)
{
}

/// компилятор сам сгенерирует такой же деструктор. нет смысла писать. лучше удалить.
//мой компилятор ругается без этой строчки
Vector2::~Vector2() {}

// fixit: лучше список инициализации (done?)
Vector2::Vector2(float kx, float ky) : x(kx), y(ky)
{
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	//return Vector2(x + other.x, y + other.y); ? одна строка вместо 4х (done?)
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator*(float k) const
{
	return Vector2(x * k, y * k);
}

Vector2 Vector2::operator/(float k) const
{
	return Vector2(x / k, y / k);
}

// fixit: операторы << и >> надо переделать с другой сигнатурой
std::ostream& operator<<(std::ostream& stream, const Vector2& v)
{
	stream << v.x << " " << v.y;
	return stream;
}

std::istream& operator>>(std::istream& stream,  Vector2& v)
{
	stream >> v.x >> v.y;
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
	// fixit: см. operator+ (done?)
	return Vector2(x - other.x, y - other.y);
}

float Vector2::operator^(const Vector2& other) const
{
	return x * other.y - y * other.x;
}

float Vector2::operator*(const Vector2& other) const
{
	return x * other.x + y * other.y;
}

float Vector2::Len() const
{
	// fixit: нужно Len посчитать через squareLen, чтобы не дублировать код
	//update
	return sqrt(SquareLen());
}

float Vector2::SquareLen() const
{
	return x * x + y * y;
}


Vector2 Vector2::Norm()
{
	// len дважны вычисляется ... вычислить корень довольно дорого (done?)
	float len = Len();
	return Vector2(x / len, y / len);
}

Vector2 Vector2::Perp()
{
	return Vector2(y, -x);
}

Vector2& Vector2::Rotate(float deg)
{
	/// fixit: готов поспорить, что код работает неверно в общем случае
	/// для вертикального вектора поделим на 0 + после того, как изменения компоненты х длина изменится ... и для у уже другая длина будет использоваться, что неверно
	//update
	float deg0 = atan(y / x), len = Len();;
	x = len *  cos(deg0 + deg / 180 * Pi);
	y = len  * sin(deg0 + deg / 180 * Pi);
	return *this;
}

Vector2 Vector2::GetRotated(float deg)
{
	/// fixit: у вас код дублируется ... причем с ошибкой. нужно одну через другую посчитать ф-ю 
	//update
	
	float deg0 = atan(y / x), len = Len();;
	return Vector2(len *  cos(deg0 + deg / 180 * Pi), len * sin(deg0 + deg / 180 * Pi));
}


	
	
