#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "Vector2.h"

//Задание окна
sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

struct Particle {
	Vector2 pos,velocity,center;
	float m,r;
};

//задание новой частицы
Particle Born(float x, float y) {
	Particle p;
	p.pos.x = x;
	p.pos.y = y;
	p.r = rand() % 4 + 2;
	p.m = p.r + rand() % 2 - 1;
	p.velocity.x = 15*(rand() % 20 - 10);
	p.velocity.y = 15*(rand() % 20 - 10);
	p.center.x = p.r * 5;
	p.center.y = p.r * 5;
	return p;
}

//Обработка столкновений
void Bounce(Particle& p1, Particle& p2) {
	Vector2 dp, d, n, v;
	d = (p2.pos + p2.center - (p1.center + p1.pos));
	n = d.norm();
	v = (p2.velocity - p1.velocity);
	/// зачем множитель 5 нужен? - эксперементально вычисленный коэффицент(когда мы задаем радиус, мы задаем его не в пикселях, а в 5 пикселях)
	if ((d.Len() <= ((p1.r + p2.r) * 5)) && (v * d <= 0))
	{
		dp = n * ((2) * (v * n) * p2.m  * p1.m / (p1.m + p2.m));
		p2.velocity = p2.velocity - dp / p2.m;
		p1.velocity = p1.velocity + dp / p1.m;
	}
}

// fixit: все ф-и и методы классов должны содержать глагол в названии (done?)

//Обработка столкновения с границами
void СollideWall(Particle& p) {
	// fixit: ясно, почему залипают шарики в стене. давайте на семинаре обсудим (done?)
	if (((p.pos.x < 0) && (p.velocity.x <0)) || ((p.pos.x >(window.getSize().x - p.r * 10))&&(p.velocity.x>0)))
		 p.velocity.x = -p.velocity.x;
	if (((p.pos.y < 0) && (p.velocity.y <0)) || ((p.pos.y >(window.getSize().y - p.r * 10))&&(p.velocity.y>0))) p.velocity.y = -p.velocity.y;
}

int main()
{
 //Время
 sf::Clock clock;
 sf::Time tm, tp;

 window.setFramerateLimit(60);

 std::vector<Particle> particles;
 const float Pi = 3.14159f;
 sf::Event event;
//Задание шейпа пули
 sf::CircleShape circle(5);
 circle.setFillColor(sf::Color::Black);
 //Основно цикл
  while (window.isOpen())
  {
	  sf::Time time = clock.getElapsedTime();
	  window.clear(sf::Color::White);

	  // Обработка нажатия кнопки мыши
	  if ((sf::Mouse::isButtonPressed(sf::Mouse::Left))&&((time.asSeconds() - tm.asSeconds())>0.25))
	  {
		 particles.push_back(
			 Born(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
		 tm = time;
	  };
	  //Проверка столкновений
	 for (size_t i = 0; i < particles.size(); ++i)
		  {
			  for (size_t j = i + 1; j < particles.size(); ++j)
			  {
				  Bounce(particles[i], particles[j]);
			  }
		  }
	// Отрисовка частницы
	  for (size_t i = 0; i < particles.size(); ++i)
	  {
		  //Задание положения частицы
		  // fixit: зачем здесь константа 15? dr = v * dt ... никакого 15 в этом уравнении нет ведь :) 
		  //- просто коэффициент, чтобы частицы не слишком медленными были, перенесла в определение частицы
		  particles[i].pos += particles[i].velocity *  (time.asSeconds() - tp.asSeconds());
		  //Столкнулись со стеной?
		  СollideWall(particles[i]);
		  //Отрисовка
		  circle.setPosition(particles[i].pos.x, particles[i].pos.y);
		  circle.setScale(particles[i].r, particles[i].r);
		  circle.setFillColor(sf::Color(255, 200 - particles[i].m * 200 / 6, 200 - particles[i].m  * 200 / 6));
		  window.draw(circle);
	  }
	  tp = time;
	  //Обработка закрытия окна
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

