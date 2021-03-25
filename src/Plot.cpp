#include "Plot.h"
Plot::Plot(Graph_info* info):_info(info){

}

Vector<sf::Vector2f> Plot::points() {
	//Create a queue of token* representing the equation
	Tokenizer token;
	Queue<Token*> infix = token(_info->_equation); //equation
	Vector<sf::Vector2f> results;
	//declare shunting yard
	shuntingYard sy(infix);
	//Run shunting yard on infix queue
	_postfix = sy.postfix();
	//Send the postfix queue to rpn
	RPN rpn;
	coord_translator ct(_info);
	double step = (_info->_domain.y-_info->_domain.x)/_info->_points;
	for (double x = _info->_domain.x; x <= _info->_domain.y; x+=step) { 
		double y_coord = rpn(_postfix,x);
		results.push_back(ct(sf::Vector2f(x,y_coord)));
	}
	//go into the infix queue and delete all the stuff in there
	while (!infix.isEmpty()) {
		delete infix.pop();
	}
	return results;
}
Vector<sf::Vector2f> Plot::operator()() {
	return points();
}