#pragma once
#include <iostream>
#include <vector>
#include "SFML\Graphics.hpp"

class Directions 
{
public:
	//   0
	//3     1
	//   2
	float dirWeights[4];
	Directions();
};

class OpponentPos
{
public:
	Directions directions;
};

class SelfPos
{
public:
	sf::Vector2i position;
	OpponentPos OpponentPos[50][50];
};

class Data 
{
public:
	SelfPos selfPos[50][50];
};

class Agent
{
public:
	sf::RectangleShape rect;
	sf::Vector2i position;
	Data data;
	bool isTarget;
	float prevDistance;
	//  self.pos self.pos 
	
	void move(int,int);
	sf::RectangleShape getRect();
	Agent(bool,sf::Vector2i);
};