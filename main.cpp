#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "Vector2.h"

//���������� ���������
struct Particle {
	Vector2 pos,velocity,center;
	float m,r;
	sf::Time t;
};
//�������� �������
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
//���������� ��� ������������
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
//������������ �� �����
void Walls(Particle& p) {
	if ((p.pos.x < 0) || (p.pos.x >(800 - p.r * 10))) p.velocity.x = -p.velocity.x;
	if ((p.pos.y < 0) || (p.pos.y >(600 - p.r * 10))) p.velocity.y = -p.velocity.y;
}

int main()
{
	//������������� �������
sf::Clock clock;
sf::Time tm;
	//������������� ����
 sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
 window.setFramerateLimit(60);
	//������ ������
 std::vector<Particle> particles;
	//��������� ��� ��������
 const float Pi = 3.14159f;
	//���������� ������
 sf::Event event;
	//���������� �����
 sf::CircleShape circle(5);
 circle.setFillColor(sf::Color::Black);
	//�������� ����
  while (window.isOpen())
  {
	  //������ �������
	  sf::Time time = clock.getElapsedTime();
	  //��������
	  window.clear(sf::Color::White);
	  // �������� �������
	  if ((sf::Mouse::isButtonPressed(sf::Mouse::Left))&&((time.asSeconds() - tm.asSeconds())>0.25))
	  {
		 particles.push_back(
			 Born(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, time));
		 tm = time;
	  };
	  // ��������� ������������
	 for (size_t i = 0; i < particles.size(); ++i)
		  {
			  for (size_t j = i + 1; j < particles.size(); ++j)
			  {
				  Bounce(particles[i], particles[j]);
			  }
		  }
	// ����������� ���������
	  for (size_t i = 0; i < particles.size(); ++i)
	  {
		  //������� ������ ���������
		  particles[i].pos += particles[i].velocity * (15 * (time.asSeconds() - particles[i].t.asSeconds()));
		  particles[i].t = time;
		  //������������ �� �����
		  Walls(particles[i]);
		  //��������� �������
		  circle.setPosition(particles[i].pos.x, particles[i].pos.y);
		  circle.setScale(particles[i].r, particles[i].r);
		  circle.setFillColor(sf::Color(255, 200 - particles[i].m * 200 / 6, 200 - particles[i].m  * 200 / 6));
		  window.draw(circle);
	  }
	  //��������� �������� ������
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
