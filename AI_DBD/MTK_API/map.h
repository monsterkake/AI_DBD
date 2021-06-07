#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include <SFML\OpenGL.hpp>

#include <iostream>
#include <vector>
#include <fstream>

class Tile
{
public:
	std::string type;
	sf::RectangleShape rect;
	Tile(std::string);
	sf::Vector2f getPosition();
	sf::RectangleShape getRect();
	void setPosition(float,float);
	
};

class Map 
{
public:
	int size = 50;
	std::vector<std::vector<Tile*>> tiles;
	void setTile(int,int, std::string);
	Map();
	~Map();
};

void writeMap();
void readMap();