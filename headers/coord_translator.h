#pragma once
#include "Vector.h"
#include "constants.h"
#include "Graph_info.h"
#include <iostream>
#include <SFML/Graphics.hpp>
class coord_translator{
public:
	coord_translator(Graph_info* info);
	sf::Vector2f translate(sf::Vector2f points);
	sf::Vector2f operator ()(sf::Vector2f points);
private:
	Graph_info* _info;
};

