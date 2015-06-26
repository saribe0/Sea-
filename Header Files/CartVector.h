/*A class that describes a vector in cartesian coordinates.
	Includes functionality for scaling a vector by a constant
	and printing the vector.*/

#include <iostream>
#include <fstream>

#ifndef CartVector_h
#define CartVector_h

class CartVector
{
public:
	double x;
	double y;

	//Default constructor creates vector <0,0>
	CartVector();

	//Constructor for CartVector with given x and y
	CartVector(double in_x, double in_y);

	//Writes a cartvector to a file
	void save(std::ofstream& file);
};

//Overloads * operator to multiply a vector by a scaler
CartVector operator* (CartVector v1, double d);

//Overloads / operator to divide a vector by a scaler
CartVector operator/ (CartVector v1, double d);

//Overloads << operator to print a vector
std::ostream& operator << (std::ostream &out, CartVector v1);

#endif