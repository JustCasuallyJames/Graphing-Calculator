#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "system.h"
#include "sidebar.h"
#include "Graph_info.h"
#include <iostream>
class animate {
public:
    animate();
    animate(const animate& RHS);
    ~animate();
    animate& operator=(const animate& RHS);
    void run();
    void processEvents();
    void update();
    void render();
    void Draw();
private:
    System system;                      //container for all the animated objects
    Sidebar sidebar;                    //rectangular message sidebar
    Graph_info* _info;
    int command;                        //command to send to system
    string _equation;                   //equation
    sf::RectangleShape function_box;    //this is the function box
    sf::Text function_text;             //this is the function text
    string equation_box;                //this is the function string

    sf::RectangleShape help_box;        //the help box
    sf::Text help_text;                 //the help texts
    bool needHelp;                      //toggle help menu

    Vector<string> writeFunctions;      //writes the functions

    sf::RenderWindow window;
    bool function_input;
    sf::CircleShape mousePoint;         //The little red dot
    sf::Font font;                      //font to draw on main screen
    sf::Text myTextLabel;               //text to draw on main screen
    bool mouseIn;                       //mouse is in the screen

    //helpful functions
    string helpful_text();
    
};

string mouse_pos_string(sf::RenderWindow& window);

#endif // GAME_H
