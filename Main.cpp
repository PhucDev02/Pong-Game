#include <SFML/Graphics.hpp> 
#include <iostream>
#include <cstdlib>
#include<math.h>
sf::RenderWindow window(sf::VideoMode(500, 500), "Pong Game", sf::Style::Close | sf::Style::Resize);
sf::RectangleShape leftBar(sf::Vector2f(20.f, 100.f));
sf::RectangleShape rightBar(sf::Vector2f(20.f, 100.f));
sf::Texture ballTexture;
sf::CircleShape ball(20.f);
sf::Font font;
sf::Text winner, pressToPlay;
float radius = ball.getRadius();
float deltaTime = 0.f;
float barSpeed = 400.0;
float ballSpeed = 400.f;
float angleBall = 32.f ;
void setText()
{
	font.loadFromFile("Pangolin.ttf");
	winner.setFont(font);
	winner.setCharacterSize(28);
	winner.setFillColor(sf::Color::Green);
	winner.setString("Press space to play");

}
void setBall()
{
	ballTexture.loadFromFile("test.png");
	ball.setTexture(&ballTexture);
	ball.setOrigin(sf::Vector2f(ball.getRadius() / 2, ball.getRadius() / 2));
	ball.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	angleBall = rand() % 43;
}
void setRightBar()
{
	rightBar.setFillColor(sf::Color::Red);
	rightBar.setOrigin(sf::Vector2f(10.f, 50.f));
	rightBar.setPosition(sf::Vector2f(490.f, 250.f));
}
void setLeftBar()
{
	leftBar.setFillColor(sf::Color::Blue);
	leftBar.setOrigin(sf::Vector2f(10.f, 50.f));
	leftBar.setPosition(sf::Vector2f(10.f, 250.f));
}
void controlRightBar()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (rightBar.getPosition().y <= 449.5)
			rightBar.move(0, barSpeed * deltaTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (rightBar.getPosition().y >= 50.5)
			rightBar.move(0, -barSpeed * deltaTime);
	}
}
void controlLeftBar()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (leftBar.getPosition().y <= 449.5)
			leftBar.move(0, barSpeed * deltaTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (leftBar.getPosition().y >= 50.5)
			leftBar.move(0, -barSpeed * deltaTime);
	}
}
void reset()
{
	setBall();
	setLeftBar();
	setRightBar();
}
int main()
{
	reset();
	setText();
	sf::Clock clock;
	int x = 0;
	bool isPlaying = 0;
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isPlaying == 0)
		{
			reset();
			isPlaying = 1;
		}
		if (isPlaying == 1)
		{
			ball.rotate(15.f*deltaTime);
			//control
			controlLeftBar();
			//controlRightBar();
			//move ball
			ball.move(ballSpeed * deltaTime * cos(angleBall * 3.14 / 180), ballSpeed * deltaTime * sin(angleBall * 3.14 / 180));
			//check va chạm biên
			rightBar.move(0, (ballSpeed - 150) * deltaTime * sin(angleBall * 3.14 / 180));
			if (ball.getPosition().y - radius < 0 || ball.getPosition().y + radius > 500)
			{
				angleBall = 360 - angleBall;
			}
			//check chạm thanh
			if (ball.getPosition().x - radius < leftBar.getPosition().x + 10
				&& ball.getPosition().y >= leftBar.getPosition().y - 50
				&& ball.getPosition().y <= leftBar.getPosition().y + 50
				&&ball.getPosition().x>leftBar.getPosition().x)
			{
				angleBall = 180 - angleBall - rand() % 10 + 10;
			}
			if (ball.getPosition().x + radius > rightBar.getPosition().x - 10
				&& ball.getPosition().y >= rightBar.getPosition().y - 50
				&& ball.getPosition().y <= rightBar.getPosition().y + 50
				&&ball.getPosition().x<rightBar.getPosition().x)
			{
				angleBall = 180 - angleBall + rand() % 10 + 10;
			}
			//set winner
			if (ball.getPosition().x < 0)
			{
				winner.setString("Red is winner\nPress space to play");
				window.draw(winner);
				isPlaying = 0;
			}
			if (ball.getPosition().x > 500)
			{
				winner.setString("Blue is winner\nPress space to play");
				window.draw(winner);
				isPlaying = 0;
			}
		}
			window.clear();
			if (isPlaying)
			{
				window.draw(leftBar);
				window.draw(ball);
				window.draw(rightBar);

			}
			else window.draw(winner);
		window.display();

	}

	return 0;
}