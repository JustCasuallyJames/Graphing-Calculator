#pragma once
#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Vector.h"
#include "Graph_info.h"
#include <vector>
#include "constants.h"

using namespace std;


class Sidebar{
public:
    Sidebar();
    Sidebar(float left, float width);
    void draw(sf::RenderWindow& window);
    string& operator [](int index);
    Vector<sf::Text> getHistoryItems();
    void udpateFunction(string func);
private:

    sf::RectangleShape rect;            //sidebar rectangle
    vector<string> items;               //strings to place on the sidebar
    sf::Font font;                      //used to draw text
    sf::Text sb_text;                   //used to draw strings on the window object
    Vector<sf::Text> _history_items;
    Graph_info* _info;
    float _left;
    float _width;
    
    //functions
    
};

#endif // SIDEBAR_H
