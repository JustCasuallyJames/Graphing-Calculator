#pragma once
#ifndef SYSTEM_H
#define SYSTEM_H
#include <SFML/Graphics.hpp>
#include "graph.h"
#include "Graph_info.h"
using namespace std;
class System{
public:
    System(Graph_info* info);
    void Step(int command, Graph_info* info);
    void Draw(sf::RenderWindow& widnow);
private:
    graph _graph;
    Graph_info* _info;
};

#endif // SYSTEM_H
