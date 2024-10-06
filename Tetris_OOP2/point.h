#ifndef _POINT_H
#define _POINT_H


class Point
{
	int x = 1, y = 1;
	int diff_x = 0, diff_y = 1;

public:
	Point(int _x, int _y); //Construct a Point with specified xand y coordinates.
	Point(); //Construct a Point with default x and y coordinates.
	Point(const Point& point) { x = point.x, y = point.y; };
	int getY(); //Get the y-coordinate of the Point.
	int getX(); //Get the x-coordinate of the Point.
	void setPoint(int _x, int _y); //Set the x and y coordinates of the Point.

};

#endif