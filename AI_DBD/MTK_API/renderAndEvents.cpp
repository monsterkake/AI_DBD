#include <thread>
#include <chrono>
#include <mutex>
#include <iostream>
#include <fstream>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include <SFML\OpenGL.hpp>

#include "renderAndEvents.h"
#include "map.h"
#include "agent.h"

sf::RenderWindow window;

extern Map map;
extern Agent agent_1;
extern Agent agent_2;

void manageEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::MouseButtonPressed:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i mPos = sf::Mouse::getPosition(window);
				int mPosx = int(sf::Mouse::getPosition(window).x / 10);
				int mPosy = int(sf::Mouse::getPosition(window).y / 10);
				if(map.tiles[mPosx][mPosy]->type == "grass")
					map.setTile(mPosx, mPosy,"wall");
				else
					map.setTile(mPosx, mPosy, "grass");
				
			}
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Q)
				window.close();
			if (event.key.code == sf::Keyboard::W)
				agent_1.move(0, -1);
			if (event.key.code == sf::Keyboard::S)
				agent_1.move(0, 1);
			if (event.key.code == sf::Keyboard::A)
				agent_1.move(-1, 0);
			if (event.key.code == sf::Keyboard::D)
				agent_1.move(1, 0);
			break;

		default: break;
		}
	}
}

void render()
{
	window.clear(sf::Color::Black);

	for (int i = 0; i < map.size; i++) 
	{
		for (int j = 0; j < map.size; j++)
		{
			window.draw(map.tiles[i][j]->getRect());
			
		}
	}
	window.draw(agent_1.getRect());
	window.draw(agent_2.getRect());
	window.display();
}

