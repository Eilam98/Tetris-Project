#include <iostream>
using namespace std;

#include "point.h"
#include "general.h"
#include "gameConfig.h"

//Construct a Point with specified xand y coordinates.
Point::Point(int _x, int _y) { x = _x; y = _y; diff_x = 0; diff_y = 1; }

//Construct a Point with default x and y coordinates.
Point::Point() { x = GameConfig::GAME_WIDTH / 2; y = 0; diff_x = 0; diff_y = 1; }
//Get the y-coordinate of the Point.
int Point::getY()
{
	return y;
}

//Get the x-coordinate of the Point.
int Point::getX()
{
	return x;
}

//Set the x and y coordinates of the Point.
void Point::setPoint(int _x, int _y) { x = _x; y = _y; }
