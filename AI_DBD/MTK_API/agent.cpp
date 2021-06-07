#include "agent.h"
#include "map.h"

extern Map map;

void Agent::move(int x, int y)
{
	if (map.tiles[this->position.x + x][this->position.y]->type != "wall") 
	{
		this->position.x += x;
		this->rect.setPosition(float(this->position.x * 10), float(this->position.y * 10));
	}
		
	if (map.tiles[this->position.x][this->position.y + y]->type != "wall")
	{
		this->position.y += y;
		this->rect.setPosition(float(this->position.x * 10), float(this->position.y * 10));
	}
		
	
}

sf::RectangleShape Agent::getRect()
{
	return this->rect;
}

Agent::Agent(bool isTarget, sf::Vector2i position)
{
	this->prevDistance = 2500;
	this->isTarget = isTarget;
	this->position = position;
	if (this->isTarget)
		this->rect.setFillColor(sf::Color::Blue);
	else
		this->rect.setFillColor(sf::Color::Red);
	this->rect.setPosition(float(this->position.x * 10), float(this->position.y * 10));
	rect.setSize(sf::Vector2f(10, 10));
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(1);
}

Directions::Directions() 
{
	dirWeights[0] = 0;
	dirWeights[1] = 0;
	dirWeights[2] = 0;
	dirWeights[3] = 0;
}

Agent agent_1(true, { 48,48 });
Agent agent_2(false, { 1,1 });