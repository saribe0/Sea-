/*Class that creates a point in terms of x and y.
	Includes functionality for adding a vector to a point,
	subtracting two points, printing a point, and finding the 
	distance between two points. */

#include "CartVector.h"
#include <iostream>
#include <fstream>

#ifndef CartPoint_h
#define CartPoint_h

class CartPoint
{
public:
	double x;
	double y;

	//Default constructor for a CartPoint at (0,0)
	CartPoint();

	//Constructor for a CartPoint with given coordinates
	CartPoint(double in_x, double in_y);

	//Writes a cartpoint to a file
	void save(std::ofstream& file);
};

//Takes two CartPoints and returns the distance between the two
double cart_distance(CartPoint p1, CartPoint p2);

//Overloads + operator to add a CartVector to a CartPoint
CartPoint operator + (CartPoint p, CartVector v);

//Overloads - operator to subtract two CartPoints to get a CartVector
CartVector operator - (CartPoint p1, CartPoint p2);

//Overloads == operator to determine if two CartPoints are the same
bool operator == (CartPoint p1, CartPoint p2);

//Overloaded << operator to print a CartPoint in form <(x,y)>
std::ostream& operator << (std::ostream &out, CartPoint p1);

#endif