#pragma once
#pragma once
#include <iostream>
#include "Vector.h"
#include "coord_translator.h"
#include "Plot.h"
#include "Graph_info.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;
class graph {
public:
	graph(Graph_info* info);
	void update();
	void draw(sf::RenderWindow& window);

private:
	Vector<sf::Vector2f> _points;
	Graph_info* _info;
	Plot _plotter;
};

