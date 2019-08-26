#include <SFML/Graphics.hpp>
//#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>


int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Snake");

	sf::Clock clock;
	sf::Clock deltaClock;

	sf::Time deltaTime = deltaClock.restart();
	sf::Time timeElapsed = deltaClock.restart();
	sf::Time lastTime = deltaClock.restart();

	sf::Text timeText;
	sf::Font arial;

	sf::Texture tileSheet;

	sf::Sprite snakeSprite;
	sf::Sprite cherry;

	sf::IntRect bounds{ 0,0,1600,900 };

	sf::Keyboard key;

	sf::Vector2i direction{ 0,0 };
	sf::Vector2f lastPosition{ 496,496 };
	
	std::vector<sf::Sprite> snake;

	double snakeSpeed = 0.15;

	bool placeApple = false;

	if (!tileSheet.loadFromFile("tiles.png"))
	{
		
	}

	snakeSprite.setTexture(tileSheet);
	snakeSprite.setTextureRect(sf::IntRect(80, 0, 16, 16));
	snakeSprite.setPosition(496, 496);
	snake.push_back(snakeSprite);

	cherry.setTexture(tileSheet);
	cherry.setTextureRect(sf::IntRect(112, 80, 16, 16));

	arial.loadFromFile("arialCE.ttf");
	timeText.setFillColor(sf::Color::Cyan);
	timeText.setFont(arial);
	timeText.setPosition(0, 0);
	timeText.setString(std::to_string(clock.getElapsedTime().asSeconds()));

	while (window.isOpen())
	{
		window.clear(sf::Color::White);
		timeElapsed += deltaTime;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		if (key.isKeyPressed(sf::Keyboard::Up))
		{
			direction.x = 0;
			direction.y = -16;
		}
		else if (key.isKeyPressed(sf::Keyboard::Down))
		{
			direction.x = 0;
			direction.y = 16;
		}
		else if (key.isKeyPressed(sf::Keyboard::Left))
		{
			direction.x = -16;
			direction.y = 0;
		}
		else if (key.isKeyPressed(sf::Keyboard::Right))
		{
			direction.x = 16;
			direction.y = 0;
		}
		
		if (timeElapsed.asSeconds() > lastTime.asSeconds() + snakeSpeed)
		{
			if ((*snake.begin()).getPosition() == cherry.getPosition())
			{
				snake.push_back(snakeSprite);
				placeApple = false;
			}
			if (snake.size() == 1) 
			{
				(*snake.begin()).setPosition(lastPosition.x + direction.x, lastPosition.y + direction.y);
				lastPosition = (*snake.begin()).getPosition();
			}
			else
			{
				sf::Vector2f lastPos = (*snake.begin()).getPosition();
				sf::Vector2f lastPos2 = (*snake.begin()).getPosition();
				(*snake.begin()).setPosition(lastPosition.x + direction.x, lastPosition.y + direction.y);
				lastPosition = (*snake.begin()).getPosition();
				for (auto i = snake.begin() + 1; i != snake.end(); ++i)
				{
					if ((*i).getPosition() == (*snake.begin()).getPosition())
					{
						return 0;
					}
					lastPos2 = (*i).getPosition();
					(*i).setPosition(lastPos.x, lastPos.y);
					lastPos = lastPos2;
				}
			}
			lastTime = timeElapsed;
		}
		if (!bounds.contains((*snake.begin()).getPosition().x, (*snake.begin()).getPosition().y))
		{
			return 0;
		}
		if (!placeApple)
		{
			cherry.setPosition((rand() % 100) * 16, (rand() % 50) * 16);
			snakeSpeed -= 0.005;
			placeApple = true;
		}

		timeText.setString(std::to_string(timeElapsed.asSeconds()));
		window.draw(cherry);
		for (auto &i : snake)
		{
			window.draw(i);
		}
		window.draw(timeText);
		
		window.display();
		deltaTime = deltaClock.restart();
	}
	return 0;
}