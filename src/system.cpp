#include "../headers/system.h"
#include "../headers/constants.h"
#include <iostream>

System::System(Graph_info* info):_info(info), _graph(info){

}

//------------------------------------------------------------------
//------------------------------------------------------------------

void System::Step(int command, Graph_info* info) {
    double PAN = (_info->_domain.y - _info->_domain.x)*.08; //percentage
   
    switch (command) {
        
        case 5: //This pans to the left
            _info->_domain.y -= PAN;
            _info->_domain.x -= PAN;
            _info->_scale.x = _info->_window_dimensions.x / (_info->_domain.y - _info->_domain.x);
            _info->_origin.x += PAN * _info->_scale.x;
            break;
        case 6: //This pans to the right
            _info->_domain.y += PAN;
            _info->_domain.x += PAN;
            _info->_scale.x = _info->_window_dimensions.x / (_info->_domain.y - _info->_domain.x);
            _info->_origin.x -= PAN * _info->_scale.x; //instead of increasing by 1 pixel, you're increasing by one tick mark

            break;
        case 7: //This is panning upwards
            _info->_origin.y += PAN * _info->_scale.x;

            break;
        case 8: //This is panning downwards
            _info->_origin.y -= PAN * _info->_scale.x;

            break;
        case 9: //This is zooming out
            //zooming is decreasing domain and increasing domain
            _info->_domain.x -= PAN;
            _info->_domain.y += PAN;
            _info->_scale.x = _info->_window_dimensions.x / (_info->_domain.y - _info->_domain.x);
            _info->_origin.x = (-_info->_domain.x) * _info->_scale.x;

            break;
        case 10: //This is zooming in
            _info->_domain.x += PAN; //increases domain and adds  (left)
            _info->_domain.y -= PAN; //decreases domain and subtracts (right)
            _info->_scale.x = _info->_window_dimensions.x / (_info->_domain.y - _info->_domain.x); //This helps scale the origin based off the domain of the graph

            _info->_origin.x = (-_info->_domain.x) * _info->_scale.x;
            break;
        default:
            break;
    }
    _graph.update();
}

void System::Draw(sf::RenderWindow& window) {
    _graph.draw(window);
}
