#include <chrono>
#include <iostream>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <random>
#include <stdio.h>
#include <math.h>

#include "calculations.h"


extern Agent agent_1;
extern Agent agent_2;

std::mutex mutex;

//int sum[4];

void decision(Agent& agent_A, Agent& agent_B,int randomNumber)
{
	if (agent_A.position == agent_B.position) 
	{
		agent_A.position = { 1,1 };
		agent_B.position = { 48,48 };
	}
		
	mutex.lock();
	int r = randomNumber % 4;
	//std::cout << r << std::endl;
	//sum[r]++;
	//for (int i = 0; i < 4; i++) 
	//{
		//std::cout << sum[i] << " | " ;
	//}
	std::cout << std::endl;
	agent_A.data.selfPos[agent_A.position.x][agent_A.position.y].OpponentPos[agent_B.position.x][agent_B.position.y].directions.dirWeights[r] += 0.005;
	float max = 0;
	int iteration = 0;
	for (int i = 0; i < 4; i++) 
	{
		if (agent_A.data.selfPos[agent_A.position.x][agent_A.position.y].OpponentPos[agent_B.position.x][agent_B.position.y].directions.dirWeights[i] > max)
		{
			max = agent_A.data.selfPos[agent_A.position.x][agent_A.position.y].OpponentPos[agent_B.position.x][agent_B.position.y].directions.dirWeights[i];
			iteration = i;
		}
	}
	switch (iteration)
	{
	case 0:
		agent_A.move(0, -1);
		break;
	case 1:
		agent_A.move(1, 0);
		break;
	case 2:
		agent_A.move(0, 1);
		break;
	case 3:
		agent_A.move(-1, 0);
		break;
	}
	float distance = sqrt(pow((agent_A.position.x - agent_B.position.x), 2) + pow((agent_A.position.y - agent_B.position.y), 2));
	
	if (agent_A.isTarget) 
	{
		if (distance > agent_A.prevDistance)
			agent_A.data.selfPos[agent_A.position.x][agent_A.position.y].OpponentPos[agent_B.position.x][agent_B.position.y].directions.dirWeights[iteration] += 1;
		if (distance < agent_A.prevDistance)
			agent_A.data.selfPos[agent_A.position.x][agent_A.position.y].OpponentPos[agent_B.position.x][agent_B.position.y].directions.dirWeights[iteration] -= 1;
		if (distance == agent_A.prevDistance)
			agent_A.data.selfPos[agent_A.position.x][agent_A.position.y].OpponentPos[agent_B.position.x][agent_B.position.y].directions.dirWeights[iteration] -= 0.1;
	}
	if (!agent_A.isTarget)
	{
		if (distance < agent_A.prevDistance)
			agent_A.data.selfPos[agent_A.position.x][agent_A.position.y].OpponentPos[agent_B.position.x][agent_B.position.y].directions.dirWeights[iteration] += 1;
		if (distance > agent_A.prevDistance)
			agent_A.data.selfPos[agent_A.position.x][agent_A.position.y].OpponentPos[agent_B.position.x][agent_B.position.y].directions.dirWeights[iteration] -= 1;
		//if (distance == agent_A.prevDistance)
		//	agent_A.data.selfPos[agent_A.position.x][agent_A.position.y].OpponentPos[agent_B.position.x][agent_B.position.y].directions.dirWeights[iteration] -= 0.5;
	}
	agent_A.prevDistance = distance;
	mutex.unlock();
}

