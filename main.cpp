#include <SFML\Graphics.hpp>
#include <iostream>
#include "Vector2.h"
#include <vector>

//Структура для пуль
struct bull {
	Vector2 v, pos;
	sf::Time t;
};

int main()
{
	//Вектор пуль
	std::vector <bull> bullets;
	//Инициализация таймера
	sf::Time tm, t_b;
	sf::Clock clock;
	//Инициализация окна
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	window.setFramerateLimit(60);
	//Текстурирование фона
	sf::Texture mapTexture;
	if (!mapTexture.loadFromFile("molumen-world-map.png"))
	{
		std::cout << "Can't load texture\n";
	}
	//Создание фона
	mapTexture.setSmooth(true);
	sf::Sprite background;
	background.setTexture(mapTexture);
	float scale = 1.0f;
	float currScale = scale;
	//Константа для поворота
	const float Pi = 3.14159f;
	//Объявление евента
	sf::Event event;
	//Модуль героя
	sf::Texture texture;
	texture.loadFromFile("hero.png");
	sf::Sprite circle(texture);
	circle.setScale(0.5f, 0.5f);
	//Векторы для реализации поворота героя 
	sf::Vector2f v1, v2;
	v1 = circle.getPosition();
	//Вектор определения скорости пули
	Vector2 v(1,0);
	//Фигура пули
	sf::CircleShape bullet(5);
	bullet.setFillColor(sf::Color::Black);
	//Переменная для создания пули
	bull b;
	//Основной цикл
	while (window.isOpen())
	{
		//Таймер
		sf::Time time = clock.getElapsedTime();
		//Зачистка
		window.clear(sf::Color::Red);
		window.draw(background);
		//Обработка закрытие экрана
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		//Поворот героя
		if (time.asSeconds() - tm.asSeconds() > 0.05)
		{
			v2 = circle.getPosition();
			if (v2 != v1)
			{
				circle.setRotation(90 + atan2f((v2.y - v1.y), (v2.x - v1.x)) * 180 / Pi);
			}
			v1 = v2;
			tm = time;
		}
		//Прорисовка пуль
		for (size_t i = 0; i < bullets.size(); ++i)
			{
				//Просчет нового положения пули
				bullets[i].pos += bullets[i].v * (500 * (time.asSeconds() - bullets[i].t.asSeconds()));
				bullets[i].t = time;
				bullet.setPosition(bullets[i].pos.x, bullets[i].pos.y);
				if ((bullets[i].pos.x > 850) || (bullets[i].pos.x < -50) || (bullets[i].pos.y > 650) || (bullets[i].pos.y < -50))
					bullets.erase(bullets.begin() + i);
				window.draw(bullet);
			}
		//Рождение пули
		if ((sf::Mouse::isButtonPressed(sf::Mouse::Left))&& (time.asSeconds() - t_b.asSeconds() > 0.2))
		{
			b.v = v.getRotated(circle.getRotation() - 90);
			b.t = time;
			b.pos.x = circle.getPosition().x;
			b.pos.y = circle.getPosition().y;
			bullets.push_back(b);
			t_b = time;
		}
		//Лазер
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) 
		{
			sf::Vertex lazer[] =
			{
				sf::Vertex(sf::Vector2f(circle.getPosition())),
				sf::Vertex(sf::Vector2f(circle.getPosition().x + 800 * v.getRotated(circle.getRotation() - 90).x, circle.getPosition().y + 800 * (v.getRotated(circle.getRotation() - 90).y)))
			};
			window.draw(lazer, 20, sf::Lines);
		}
		//Движение по клавишам
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (circle.getPosition().x> 0))
			circle.move(-1.5, 0);
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && (circle.getPosition().x<800))
			circle.move(1.5, 0);
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (circle.getPosition().y>0))
			circle.move(0, -1.5);
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down))&&(circle.getPosition().y<600))
			circle.move(0, 1.5);
		//Отрисовка
		window.draw(circle);
		window.display();
	}
	return 0;
}