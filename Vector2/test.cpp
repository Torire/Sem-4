#include "Vector2.h"

int main() 
{
	const Vector2 v2(3, 4);
	Vector2 v;
	float k, deg;
	
	std::cout << "Введите двумерный вектор(координаты x и y, вектор длаьше обозначается v)" << "\n";
	v >> std::cin;
	std::cout << "Введите число(дальше k)" << "\n";
	std::cin >> k; 
	std::cout << "Введите угол в градусах(дальше deg)" << "\n";
	std::cin >> deg; 
	std::cout << "Длина вектора: " << v.Len() << "\n";
	std::cout << "Введен вектор:";
	v << std::cout;
	std::cout << "\n";
	std::cout << "(v,(3,4)) = " << v * v2 << "\n";
	std::cout << "[v,(3,4)] = " << (v ^ v2) << "\n";
	std::cout << "Единичный вектор: " ;
	v.norm() << std::cout;
	std::cout << "\n";
	std::cout << "Перпендикуляр: " ;
	v.perp() << std::cout;
	std::cout << "\n";
	std::cout << "Поворот на угол: " ;
	v.getRotated(deg) << std::cout;
	std::cout << "\n";
	std::cout << "v + (3,4) = " ;
	(v + v2) << std::cout;
	std::cout << "\n";
	std::cout << "v - (3,4) = " ;
	(v - v2) << std::cout;
	std::cout << "\n";
	std::cout << "v += (3,4): " ;
	(v += v2) << std::cout;
	std::cout << "\n";
	std::cout << "v -= (3,4): " ;
	(v -= v2) << std::cout;
	std::cout << "\n";
	v.rotate(deg);
	std::cout << "Повернем на угол: " ;
	v << std::cout;
	std::cout << "\n";
	
	return 0;
}
