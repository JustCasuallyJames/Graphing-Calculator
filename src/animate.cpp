
#include <iostream>
#include <fstream>
#include "../headers/animate.h"
#include "../headers/constants.h"
#include "../headers/system.h"
using namespace std;
animate::animate() :sidebar(WORK_PANEL, SIDE_BAR), system(_info = new Graph_info()){
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML window!");
    //string equation, window dimensions, origin, scale, domain, points
    _equation = "1 / 0";
    _info->_domain = sf::Vector2f(-5, 5);
    _info->_equation = _equation;
    _info->_origin = sf::Vector2f(WORK_PANEL/2,SCREEN_HEIGHT / 2);
    _info->_scale = sf::Vector2f(WORK_PANEL / (2 * X_MAX), (SCREEN_HEIGHT / (2 * X_MAX)));
    _info->_window_dimensions = sf::Vector2f(WORK_PANEL, SCREEN_HEIGHT);
    _info->_points = 500;

    //System will be implemented to manage a vector of objects to be animated.
    //  at that point, the constructor of the System class will take a vector
    //  of objects created by the animate object.
    ////  animate will
    window.setFramerateLimit(60);

    mouseIn = true;


    mousePoint = sf::CircleShape();
    mousePoint.setRadius(5.0);
    mousePoint.setFillColor(sf::Color::Red);

    //--- FONT ----------
    //font file must be in the "working directory:
    //      debug folder
    //Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    //font must be a member of the class.
    //  Will not work with a local declaration
    if (!font.loadFromFile("arial.ttf")) {
        cout << "animate() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }

    myTextLabel = sf::Text("Current Function: " , font);
    myTextLabel.setCharacterSize(20);
    myTextLabel.setStyle(sf::Text::Bold);
    /*myTextLabel.setColor(sf::Color::Green);*/
    myTextLabel.setPosition(sf::Vector2f(10, SCREEN_HEIGHT - 30));

    //sets up the function box to be displayed
    function_box = sf::RectangleShape(sf::Vector2f(300, 100));
    function_box.setPosition(sf::Vector2f(WORK_PANEL / 4, 0));
    function_box.setFillColor(sf::Color::Green);

    //sets up the function text to be displayed
    function_text.setFont(font);
    function_text.setCharacterSize(20);
    function_text.setFillColor(sf::Color::Blue);
    function_text.setPosition((WORK_PANEL / 4) + 10, 30);

    //sets up the help box
    help_box = sf::RectangleShape(sf::Vector2f(400, 400));
    help_box.setPosition(sf::Vector2f(_info->_origin.x-195,_info->_origin.y-200));
    //(182, 55, 133)
    help_box.setFillColor(sf::Color::Blue);

    //sets up the text of the help box
    help_text.setFont(font);
    help_text.setCharacterSize(20);
    //(182, 239, 87)
    help_text.setFillColor(sf::Color::Green);
    //_info->_origin.x, _info->_origin.y
    help_text.setPosition(sf::Vector2f(_info->_origin.x - 195, _info->_origin.y - 200));
    help_text.setString(helpful_text());

}
animate::~animate() {
    delete _info;

}
//copy instructor
//initialized system, sidebar, copy all the static variables, graph info stuff too
animate::animate(const animate& RHS):system(_info = new Graph_info()),sidebar(RHS.sidebar){
    
    system = RHS.system;
    sidebar = RHS.sidebar;
    _equation = RHS._equation;
    function_box = RHS.function_box;
    mousePoint = RHS.mousePoint;
    font = RHS.font;
    myTextLabel = RHS.myTextLabel;

    _info->_domain = RHS._info->_domain;
    _info->_equation = RHS._info->_equation;
    _info->_origin = RHS._info->_origin;
    _info->_points = RHS._info->_points;
    _info->_scale = RHS._info->_scale;
    _info->_window_dimensions = RHS._info->_window_dimensions;
}
animate& animate::operator=(const animate& RHS) {
    if (this == &RHS) {
        return *this;
    }
    delete _info;
    _info = nullptr;
    _info = new Graph_info();

    system = RHS.system;
    sidebar = RHS.sidebar;
    _equation = RHS._equation;
    function_box = RHS.function_box;
    mousePoint = RHS.mousePoint;
    font = RHS.font;
    myTextLabel = RHS.myTextLabel;

    //setting variables for the graph info
    _info->_domain = RHS._info->_domain;
    _info->_equation = RHS._info->_equation;
    _info->_origin = RHS._info->_origin;
    _info->_points = RHS._info->_points;
    _info->_scale = RHS._info->_scale;
    _info->_window_dimensions = RHS._info->_window_dimensions;

    return *this;
}

void animate::Draw() {
    //Look at the data and based on the data, draw shapes on window object.
    system.Draw(window);
    if (mouseIn) {
        window.draw(mousePoint);
    }

    sidebar.draw(window);

    //- - - - - - - - - - - - - - - - - - -
    //getPosition() gives you screen coords, getPosition(window) gives you window coords
    //cout<<"mosue pos: "<<sf::Mouse::getPosition(window).x<<", "<<sf::Mouse::getPosition(window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -

    //drawing Test: . . . . . . . . . . . .
    //This is how you draw text:)
    window.draw(myTextLabel);
    //. . . . . . . . . . . . . . . . . . .

    //Doing function input
    
    if (function_input) {
        window.draw(function_box);
        window.draw(function_text);
    }
    if (_info->_equation == "1 / 0") {
        myTextLabel.setString("Current Function: none");
        window.draw(myTextLabel);
    }
    else {
        myTextLabel.setString("Current Function: " + _info->_equation);
        window.draw(myTextLabel);
    }
    
    //draws the help menu
    if (needHelp) {
        window.draw(help_box);
        window.draw(help_text);
    }


}

void animate::update() {
    //cause changes to the data for the next frame
    system.Step(command,_info);
    command = 0;
    if (mouseIn) {
        //mousePoint red dot:
        mousePoint.setPosition(sf::Mouse::getPosition(window).x - 5,
            sf::Mouse::getPosition(window).y - 5);

        //mouse location text for sidebar:
        sidebar[SB_MOUSE_POSITION] = mouse_pos_string(window);
    }
}
void animate::render() {
    window.clear();
    Draw();
    window.display();
}

void animate::processEvents()
{
    sf::Event event;
    float mouseX, mouseY;
    
    while (window.pollEvent(event))//or waitEvent
    {
        // check the type of the event...
        switch (event.type){
            // window closed
        case sf::Event::Closed:
            
            window.close();
            break;

        case sf::Event::TextEntered:
            if (function_input) {
                if (event.text.unicode < 128) {
                    if (event.text.unicode == '\b') { //checks if it's a backspace
                        if (equation_box.size() > 0) {//checks if it the string in the box is not 0
                            //deletes the last character
                            equation_box.erase(equation_box.size() - 1, 1);
                            function_text.setString(equation_box);
                        }
                    }
                    else{//This adds any character that is typed
                        equation_box += event.text.unicode;
                        function_text.setString(equation_box);
                    }
                }
            }
            break;
            // key pressed
        case sf::Event::KeyPressed:
            switch (event.key.code) {
            case sf::Keyboard::Left:
                sidebar[SB_KEY_PRESSED] = "LEFT ARROW";
                command = 5;
                system.Step(command, _info);
                break;
            case sf::Keyboard::Right:
                sidebar[SB_KEY_PRESSED] = "RIGHT ARROW";
                command = 6;
                system.Step(command, _info);
                break;
            case sf::Keyboard::Up:
                sidebar[SB_KEY_PRESSED] = "UP ARROW";
                command = 7;
                system.Step(command, _info);
                break;
            case sf::Keyboard::Down:
                sidebar[SB_KEY_PRESSED] = "DOWN ARROW";
                command = 8;
                system.Step(command, _info);
                break;
            case sf::Keyboard::LBracket:
                sidebar[SB_KEY_PRESSED] = "LEFT BRACKET";
                command = 9;
                system.Step(command, _info);
                break;
            case sf::Keyboard::RBracket:
                sidebar[SB_KEY_PRESSED] = "RIGHT BRACKET";
                command = 10;
                system.Step(command, _info);
                break;
            case sf::Keyboard::Escape:
                sidebar[SB_KEY_PRESSED] = "ESC: EXIT";
                window.close();
                break;
            case sf::Keyboard::BackSlash: //creating a function
                equation_box = "";
                function_text.setString("f(x)= ");
                sidebar[SB_KEY_PRESSED] = "FUNCTION INPUT";
                function_input = true; //can toggle the function on and off
                window.pollEvent(event);
                break;
            case sf::Keyboard::Enter:
                function_input = false; //This disables the function box
                function_text.setString(equation_box); //sets the function text to the equation you inputted
                _info->_equation = equation_box; //sets the actual equation to the equation you inputted
                writeFunctions.push_back(_info->_equation);
                sidebar.udpateFunction(_info->_equation); //updates the function and puts it to the sidebar
                break;
            case sf::Keyboard::H:
                needHelp = true;
                sidebar[SB_KEY_PRESSED] = "HELP MENU";
                break;
            case sf::Keyboard::K:
                needHelp = false;
                break;
            }
        case sf::Event::MouseEntered:
            mouseIn = true;
            break;

        case sf::Event::MouseLeft:
            mouseIn = false;
            break;

        case sf::Event::MouseMoved:
            mouseX = event.mouseMove.x;
            mouseY = event.mouseMove.y;
            break;
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left){
                sidebar[SB_MOUSE_CLICKED] = "LEFT CLICK " +
                    mouse_pos_string(window);  
                //This gets 10 values from the history.txt starting 10 spaces from the end of the file so it 
                //has the illusion that it's actually saving it at the top.
                for (int i = sidebar.getHistoryItems().get_size()-1; i >= 0; i--) {
                    if (sidebar.getHistoryItems()[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                        _info->_equation = sidebar.getHistoryItems()[i].getString();
                    }
                }
            }
            else {
                sidebar[SB_MOUSE_CLICKED] = "RIGHT CLICK " +
                    mouse_pos_string(window);
            }
            break;

        default:
            break;
        }
    }
}

void animate::run(){
    while (window.isOpen())
    {
        processEvents();
        update();
        render(); //clear/draw/display
    }
    ofstream write("history.txt", ios::app | ios::out | ios::trunc);
    write.open("history.txt", ios::app);
    for (int i = 0; i < writeFunctions.get_size(); i++) {
        if (write.is_open()) {
            write << writeFunctions[i];
            write << "\n";
        }
    }
    write.close();
}

string mouse_pos_string(sf::RenderWindow& window) {
    return "(" +
        to_string(sf::Mouse::getPosition(window).x) +
        ", " +
        to_string(sf::Mouse::getPosition(window).y) +
        ")";
}
string animate::helpful_text(){
    string help = "\n                         CONTROLS\n";
    help += "\n\n   ZOOM IN: ]\n   ZOOM OUT: [";
    help += "\n\n   LEFT: <\n   RIGHT: >\n   UP: ^\n   DOWN: v";
    help += "\n\n   INPUT EQUATION: \\ ";
    help += "\n\n   PRESS [K] TO EXIT MAIN MENU ";
    help += "\n\n   PRESS [ESC] TO EXIT PROGRAM";
    return help;
}

