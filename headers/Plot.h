#pragma once
#include "Vector.h"
#include "shuntingYard.h"
#include "RPN.h"
#include "coord_translator.h"
#include "Graph_info.h"
#include "Tokenizer.h"
#include <SFML/Graphics.hpp>
class Plot{
public:
	Plot(Graph_info* info);
	Vector<sf::Vector2f> points();
	Vector<sf::Vector2f> operator()();
private:
	Queue<Token*> _postfix; //not neccessary
	Graph_info* _info;
};

