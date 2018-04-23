#include "Vector2.h"

int main() 
{
	const Vector2 v2(3, 4);
	Vector2 v;
	float k, deg;

	std::cout << "Введите двумерный вектор(координаты x и y, вектор длаьше обозначается v)" << "\n";
	std::cin >> v;
	std::cout << "Введите число(дальше k)" << "\n";
	std::cin >> k;
	std::cout << "Введите угол в градусах(дальше deg)" << "\n";
	std::cin >> deg;
	std::cout << "Длина вектора: " << v.Len() << "\n";
	std::cout << "Введен вектор:";
	std::cout << v;
	std::cout << "\n";
	std::cout << "(v,(3,4)) = " << v * v2 << "\n";
	std::cout << "[v,(3,4)] = " << (v ^ v2) << "\n";
	std::cout << "Единичный вектор: ";
	std::cout << v.Norm();
	std::cout << "\n";
	std::cout << "Перпендикуляр: ";
	std::cout << v.Perp();
	std::cout << "\n";
	std::cout << "Поворот на угол: ";
	std::cout << v.GetRotated(deg);
	std::cout << "\n";
	std::cout << "v + (3,4) = ";
	std::cout << (v + v2);
	std::cout << "\n";
	std::cout << "v - (3,4) = ";
	std::cout << (v - v2);
	std::cout << "\n";
	std::cout << "v += (3,4): ";
	std::cout << (v += v2)  ;
	std::cout << "\n";
	std::cout << "v -= (3,4): ";
	std::cout << (v -= v2);
	std::cout << "\n";
	v.Rotate(deg);
	std::cout << "Повернем на угол: ";
	std::cout << v;
	std::cout << "\n";
	
	return 0;
}
