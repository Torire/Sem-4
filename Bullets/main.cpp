#include <SFML\Graphics.hpp>
#include <iostream>
#include "Vector2.h"
#include <vector>

/*
Замечания по Vector2 посмотрите в предыдущем упражнении
*/

sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

//Структура пули
struct bull {
	Vector2 v, pos;
	// зачем каждой пуле хранить какое-то время? 
	//update: уже не хранит
};

int main()
{
	std::vector <bull> bullets;

	// fixit: неинформативные название переменных tm и t_b (done?)
	sf::Time t_hero, t_hero_rotate, t_bullets, t_mouse;
	
	sf::Clock clock;

	window.setFramerateLimit(60);
	float velocity_constant = sqrt(window.getSize().x * window.getSize().x + window.getSize().y*window.getSize().y) / 2;
	
	float move_hero;

	sf::Texture mapTexture;
	if (!mapTexture.loadFromFile("molumen-world-map.png"))
	{
		std::cout << "Can't load texture\n";
	}
	
	mapTexture.setSmooth(true);
	sf::Sprite background;
	background.setTexture(mapTexture);
	float scale = 1.0f;
	float currScale = scale;
	
	const float Pi = 3.14159f;

	sf::Event event;
	
	sf::Texture texture;
	texture.loadFromFile("hero.png");
	sf::Sprite circle(texture);
	circle.setScale(0.5f, 0.5f);
	circle.setOrigin(50, 50);
	
	sf::Vector2f v1, v2;
	v1 = circle.getPosition();

	Vector2 v(1, 0);

	sf::CircleShape bullet(5);
	bullet.setFillColor(sf::Color::Black);
	
	bull b;
	
	while (window.isOpen())
	{
		
		sf::Time time = clock.getElapsedTime();
		
		window.clear(sf::Color::Red);
		window.draw(background);
		
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		//Обработка положения героя
		if (time.asSeconds() - t_hero_rotate.asSeconds() > 0.05)
		{
			v2 = circle.getPosition();
			if (v2 != v1) // кажется, что эта проверка не нужна ... atan2 отработает в любом случае
				//сделана только для оптимизации и чтобы ошибки какой не возникло вдруг(зачем поворачиваться, если двигаемся в том же направлении?)
			{
				circle.setRotation(90 + atan2f((v2.y - v1.y), (v2.x - v1.x)) * 180 / Pi);
			}
			v1 = v2;
			t_hero_rotate = time;
		}
		
		for (size_t i = 0; i < bullets.size(); ++i)
		{

			// не здорово использовать неименованные константы
			// эти константы лучше задавать не в пикселях сразу, а как доля от диагонали окна, например
			// тогда при изменении размера окна все нормально будет (done?) определяется в самом начале 
			bullets[i].pos += bullets[i].v * ( velocity_constant * (time.asSeconds() - t_bullets.asSeconds()));
			bullet.setPosition(bullets[i].pos.x, bullets[i].pos.y);
			if ((bullets[i].pos.x > window.getSize().x + 50) || (bullets[i].pos.x < -50) || (bullets[i].pos.y > window.getSize().y +50) || (bullets[i].pos.y < -50))
				bullets.erase(bullets.begin() + i);
			window.draw(bullet);
		}
		t_bullets = time;
		
		if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (time.asSeconds() - t_mouse.asSeconds() > 0.2))
		{
			b.v = v.getRotated(circle.getRotation() - 90);
			b.pos.x = circle.getPosition().x;
			b.pos.y = circle.getPosition().y;
			bullets.push_back(b);
			t_mouse = time;
		}
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vertex lazer[] =
			{
				sf::Vertex(sf::Vector2f(circle.getPosition())),
				sf::Vertex(sf::Vector2f(circle.getPosition().x + 800 * v.getRotated(circle.getRotation() - 90).x, circle.getPosition().y + 800 * (v.getRotated(circle.getRotation() - 90).y)))
			};
			window.draw(lazer, 20, sf::Lines);
		}
		
		move_hero = velocity_constant * ((time.asSeconds() - t_hero.asSeconds())/10);

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (circle.getPosition().x> 0))
			/// у вас скорость движения персонажа зависит от fps (мощности компьютера) ...
			/// обычно вычисляют dt между кадрами и умножают на скорость движения (константа) (done?)
			circle.move(-move_hero, 0);
		/// fixit: вместо 800 нужно написать что-то вроде window.getSize().x (done?)
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && (circle.getPosition().x<window.getSize().x))
			circle.move(move_hero, 0);
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (circle.getPosition().y>0))
			circle.move(0, -move_hero);
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && (circle.getPosition().y<window.getSize().y))
			circle.move(0, move_hero);
		t_hero = time;

		window.draw(circle);
		window.display();
	}
	return 0;
}
