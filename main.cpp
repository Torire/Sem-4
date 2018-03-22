#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "Vector2.h"

//Объявление структуры
struct Particle {
	Vector2 pos,velocity,center;
	float m,r;
	sf::Time t;
};
//Рождение частицы
Particle Born(float x, float y, sf::Time t) {
	Particle p;
	p.pos.x = x;
	p.pos.y = y;
	p.r = rand() % 4 + 2;
	p.m = p.r + rand() % 2 - 1;
	p.velocity.x = rand() % 20 - 10;
	p.velocity.y = rand() % 20 - 10;
	p.center.x = p.r * 5;
	p.center.y = p.r * 5;
	p.t = t;
	return p;
}
//Перерасчет при столкновении
void Bounce(Particle& p1, Particle& p2) {
	Vector2 dp, d, n, v;
	d = (p2.pos + p2.center - (p1.center + p1.pos));
	n = d.norm();
	v = (p2.velocity - p1.velocity);
	if ((d.Len() <= ((p1.r + p2.r) * 5)) && (v * d <= 0))
	{
		dp = n * ((2) * (v * n) * p2.m  * p1.m / (p1.m + p2.m));
		p2.velocity = p2.velocity - dp / p2.m;
		p1.velocity = p1.velocity + dp / p1.m;
	}
}
//Столкновение об стену
void Walls(Particle& p) {
	if ((p.pos.x < 0) || (p.pos.x >(800 - p.r * 10))) p.velocity.x = -p.velocity.x;
	if ((p.pos.y < 0) || (p.pos.y >(600 - p.r * 10))) p.velocity.y = -p.velocity.y;
}

int main()
{
	//Инициализация таймера
sf::Clock clock;
sf::Time tm;
	//Инициализация окна
 sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
 window.setFramerateLimit(60);
	//Вектор частиц
 std::vector<Particle> particles;
	//Константа для поворота
 const float Pi = 3.14159f;
	//Объявление евента
 sf::Event event;
	//Объявление круга
 sf::CircleShape circle(5);
 circle.setFillColor(sf::Color::Black);
	//Основной цикл
  while (window.isOpen())
  {
	  //Запуск времени
	  sf::Time time = clock.getElapsedTime();
	  //Зачистка
	  window.clear(sf::Color::White);
	  // Рождение частицы
	  if ((sf::Mouse::isButtonPressed(sf::Mouse::Left))&&((time.asSeconds() - tm.asSeconds())>0.25))
	  {
		 particles.push_back(
			 Born(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, time));
		 tm = time;
	  };
	  // Обработка столкновений
	 for (size_t i = 0; i < particles.size(); ++i)
		  {
			  for (size_t j = i + 1; j < particles.size(); ++j)
			  {
				  Bounce(particles[i], particles[j]);
			  }
		  }
	// Отображение положения
	  for (size_t i = 0; i < particles.size(); ++i)
	  {
		  //Просчет нового положения
		  particles[i].pos += particles[i].velocity * (15 * (time.asSeconds() - particles[i].t.asSeconds()));
		  particles[i].t = time;
		  //Столкновение об стены
		  Walls(particles[i]);
		  //Рисование частицы
		  circle.setPosition(particles[i].pos.x, particles[i].pos.y);
		  circle.setScale(particles[i].r, particles[i].r);
		  circle.setFillColor(sf::Color(255, 200 - particles[i].m * 200 / 6, 200 - particles[i].m  * 200 / 6));
		  window.draw(circle);
	  }
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
	window.display();
  }
  return 0;
}
