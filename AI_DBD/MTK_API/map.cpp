#include "map.h"

int tileMap[50][50];

void Map::setTile(int x, int y, std::string type)
{
	this->tiles[x][y]->type = type;
	if(type == "grass")
		this->tiles[x][y]->rect.setFillColor(sf::Color::Green);
	if (type == "wall")
		this->tiles[x][y]->rect.setFillColor(sf::Color::Black);
}

Map::Map()
{
	readMap();
	for (int i = 0; i < size; i++) 
	{
		std::vector<Tile*> temp;
		for (int j = 0; j < size; j++)
		{

			if (tileMap[i][j] == 0) 
			{
				Tile* tile = new Tile("grass");
				temp.push_back(tile);
			}

			if (tileMap[i][j] == 1)
			{
				Tile* tile = new Tile("wall");
				temp.push_back(tile);
			}

			temp[j]->setPosition(i * 10, j * 10);
		}
		tiles.push_back(temp);
	}
}

Tile::Tile(std::string type)
{
	this->type = type;
	if(this->type == "grass")
		rect.setFillColor(sf::Color::Green);
	if (this->type == "wall")
		rect.setFillColor(sf::Color::Black);

	rect.setSize(sf::Vector2f(10,10));
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(1);
}

sf::Vector2f Tile::getPosition()
{
	return this->rect.getPosition();
}

sf::RectangleShape Tile::getRect()
{
	return this->rect;
}

void Tile::setPosition(float x, float y)
{
	this->rect.setPosition(sf::Vector2f(x, y));
}

Map::~Map() 
{
	
	for (int i = 0; i < size; i++)
	{
		for (int j = size-1; j >=0 ; j--)
		{
			if (tiles[i][j]->type == "grass")
				tileMap[i][j] = 0;
			if (tiles[i][j]->type == "wall")
				tileMap[i][j] = 1;
			delete tiles[i][j];
		}
	}
	writeMap();
}

Map map;

using namespace std;

void writeMap() 
{
	std::ofstream wf("map.dat", std::ios::out | std::ios::binary);
	wf.clear();
	for(int i=0;i<50;i++)
		for (int j = 0; j < 50; j++)
			wf.write((char*)tileMap, sizeof(int[50][50]));
	wf.close();
}

void readMap()
{
	std::ifstream rf("map.dat", std::ios::out | std::ios::binary);
	if (!rf) {
		cout << "Cannot open file!" << endl;
	}
	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 50; j++) 
		{
			rf.read((char*)tileMap, sizeof(int[50][50]));
		}
			
	rf.close();
}