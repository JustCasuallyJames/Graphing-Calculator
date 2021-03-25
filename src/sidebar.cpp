#include "../headers/sidebar.h"
#include <fstream>
#include <sstream>

Sidebar::Sidebar() {

}

Sidebar::Sidebar(float left, float width) :_left(left), _width(width) {

    //set up the sidebar rectangle:
    rect.setFillColor(sf::Color(105, 105, 105)); //(192,192,192)); //silver
    rect.setPosition(sf::Vector2f(left, 0));
    rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));

    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //the font file must be in the "working directory"
    // check projects->run->working directory
    //      [Make sure it's not pointing to the app file]

    if (!font.loadFromFile("Roboto-Thin.ttf")) {
        std::cout << "Sidebar() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }
    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    sb_text.setFont(font);
    sb_text.setCharacterSize(20);
    sb_text.setStyle(sf::Text::Bold);

    ////this is how you would position text on screen:
    items.push_back("sidebar sample text");
    //Fill the items vector with empty strings so that we can use [] to read them:
    for (int i = 0; i < 30; i++) {
        items.push_back("");
    }

    int minOfFunctions = 1; //Needed to have a first value (10 values from the end)
    int numberOfFunctions = 1; //Needed so we know how many fucntions are in the file
    ifstream readFunc;
    string line;
    readFunc.open("history.txt");
    //This is only needed to get the size of how many functions are in the file
    while (getline(readFunc, line)) {
        numberOfFunctions++; //keeps adding until the end of the file
    }
    int counter = 1; //This is a counter so that when you read the file, it disregards all previous history
    ifstream read;
    string equation;
    //starts at the value 10 spaces before the last value 
    minOfFunctions = numberOfFunctions - 10;
    double height_functions = SCREEN_HEIGHT - (SCREEN_HEIGHT / 4);
    read.open("history.txt");
    //initialization
    if (_history_items.empty()) {
        sf::Text temp;
        //double height_functions = SCREEN_HEIGHT - (SCREEN_HEIGHT / 4);
        temp.setString("sin ( x )");
        temp.setPosition(sf::Vector2f(_left + LEFT_MARGIN, height_functions));
        height_functions -= temp.getLocalBounds().height + VERTICAL_LINE_SPACING;
        _history_items.push_back(temp);
    }
    while (getline(read, equation)) {
        if (minOfFunctions <= numberOfFunctions && counter >= minOfFunctions) {//starts at the value 10 spots from the end value
            sf::Text _history;
            //sets the font,color, outline color, characterSize and the string
            _history.setOutlineColor(sf::Color::White);
            _history.setFillColor(sf::Color::White);
            _history.setFont(font);
            _history.setCharacterSize(20);
            _history.setString(equation);
            //this sets the position of the very last value in the txt file to be at the top
            _history.setPosition(sf::Vector2f(_left + LEFT_MARGIN, height_functions));//sets the position at the initial height 
            height_functions -= _history.getLocalBounds().height + VERTICAL_LINE_SPACING; //Sets the height of the equations to be higher
            _history_items.push_back(_history);
            minOfFunctions++;
        }
        counter++;
    }
    read.close();
}

void Sidebar::draw(sf::RenderWindow& window) {
    window.draw(rect);
    float height = 10;
    for (vector<string>::iterator it = items.begin();
        it != items.end(); it++) {
        bool blank = false;
        if (strlen(it->c_str()) == 0) {
            //empty rows must be taken into account (getLocalBounds())
            //    but not drawn
            blank = true;
            sb_text.setString("BLANK");
        }
        else {
            sb_text.setString(it->c_str());
        }
        sb_text.setPosition(sf::Vector2f(_left + LEFT_MARGIN, height));
        height += sb_text.getLocalBounds().height + VERTICAL_LINE_SPACING;
        if (!blank) {
            window.draw(sb_text);
        }
    }
    int counter = 0;
    //draws 10 functions starting at the bottom-10 and ending at the bottom of the file.
    for (int i = _history_items.get_size(); i >= 0; i--, counter++) {
        if (counter > 10) {
            break;
        }
        else {
            window.draw(_history_items[i]);
        }
    }
    //This is the text that displays if you need help
    sf::Text pressHelp;
    pressHelp.setCharacterSize(20);
    pressHelp.setPosition(5, 20);
    pressHelp.setFillColor(sf::Color::White);
    pressHelp.setFont(font);
    pressHelp.setString("PRESS [H] FOR HELP MENU");
    window.draw(pressHelp);
}

string& Sidebar::operator [](int index) {
    return items[index];
}

Vector<sf::Text> Sidebar::getHistoryItems(){
    return _history_items;
}
void Sidebar::udpateFunction(string func){
    sf::Text temp;
    temp.setString(func);
    temp.setOutlineColor(sf::Color::White);
    temp.setFillColor(sf::Color::White);
    temp.setFont(font);
    temp.setCharacterSize(20);
    temp.setString(func);

    sf::Text t = _history_items.back(); //gets the most recent function
    double y = t.getPosition().y;
    for (int i = 0; i < _history_items.get_size(); i++) {
        double x = _history_items[i].getPosition().x;
        double y2 = _history_items[i].getPosition().y + _history_items[i].getCharacterSize(); //it puts it above the last character
        _history_items[i].setPosition(x, y2);
    }
    temp.setPosition(sf::Vector2f(_left + LEFT_MARGIN, y));//sets the position at the initial height 
    _history_items.push_back(temp);
    
}
