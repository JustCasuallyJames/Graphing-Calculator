#pragma once
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;

struct Graph_info {
	string _equation; //the equation you're trying to graph
	sf::Vector2f _window_dimensions; //how big the window dimensions are
	sf::Vector2f _origin; //where the origin of the screen is (0,0)
	sf::Vector2f _scale; //the scale of the graph
	sf::Vector2f _domain; //the domain from x-x1
	int _points; //represents the number of points that you have

};

	

