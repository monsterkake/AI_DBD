#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

#include "renderAndEvents.h"
#include "calculations.h"
#include "agent.h"

extern sf::RenderWindow window;
extern Agent agent_1;
extern Agent agent_2;

void init() 
{
    //window.create(sf::VideoMode(), "main", sf::Style::Fullscreen);
    window.create(sf::VideoMode(500,500), "main");
    window.setFramerateLimit(60);
};

void mainLoop() 
{
    while (window.isOpen()) 
    {
        int r = rand();
        std::thread t1(decision, std::ref(agent_1), std::ref(agent_2), r);
        std::thread t2(decision, std::ref(agent_2), std::ref(agent_1), r);
        //decision(agent_2, agent_1);
        render();
        manageEvents();
        t1.join();
        t2.join();

    }
}

int main()
{
    init();
    
    
    mainLoop();
    //t1.join();
    return 0;
}

