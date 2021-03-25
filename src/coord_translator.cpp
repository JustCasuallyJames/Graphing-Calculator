#include "../headers/coord_translator.h"


coord_translator::coord_translator(Graph_info* info):_info(info) {

}

sf::Vector2f coord_translator::translate(sf::Vector2f points){
	float x_coord, y_coord;
	x_coord = _info->_origin.x + points.x * _info->_scale.x;
	y_coord = _info->_origin.y + (-points.y) * _info->_scale.y;
	return sf::Vector2f(x_coord, y_coord);
}
sf::Vector2f coord_translator::operator ()(sf::Vector2f points) {
	return translate(points);
}