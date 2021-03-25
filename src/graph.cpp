#include "../headers/graph.h"
graph::graph(Graph_info* info): _info(info), _plotter(info){}
void graph::update() {
	_points = _plotter();
}
void graph::draw(sf::RenderWindow& window) {
	sf::RectangleShape x_axis(sf::Vector2f(1, SCREEN_HEIGHT));
	x_axis.setPosition(sf::Vector2f(_info->_origin.x, 0));
	window.draw(x_axis);
	sf::RectangleShape y_axis(sf::Vector2f(WORK_PANEL, 1));
	y_axis.setPosition(sf::Vector2f(0, _info->_origin.y));
	window.draw(y_axis);
	sf::CircleShape point(1);
	for (int i = 0; i < _points.get_size(); i++) {
		point.setPosition(_points[i]); // move item i from the _points
		point.setFillColor(sf::Color::Green);
		window.draw(point);
	}
}