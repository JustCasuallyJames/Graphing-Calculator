#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H
const float SCREEN_WIDTH = 1600;
const float SCREEN_HEIGHT = 1000; //800
const float X_MAX = 5;
const float Y_MAX = 25;
const float WORK_PANEL = SCREEN_WIDTH * 4 / 5;
const float SIDE_BAR = SCREEN_WIDTH * 1 / 5;

//sidebar constants
const double VERTICAL_LINE_SPACING = 5.0;
const double LEFT_MARGIN = 10.0;


//function constants
const double EULER = 2.71828182845904523536;

const int SB_MOUSE_POSITION = 0;
const int SB_MOUSE_CLICKED = SB_MOUSE_POSITION + 1;
const int SB_KEY_PRESSED = SB_MOUSE_CLICKED + 1;
#endif // CONSTANTS_H
