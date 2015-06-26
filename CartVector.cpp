#include "CartVector.h"

//Default constructor creates vector <0,0>
CartVector::CartVector()
	{
		x = 0;
		y = 0;
	}

//Constructor for CartVector with given x and y
CartVector::CartVector(double in_x, double in_y)
	{
		x = in_x;
		y = in_y;
	}

//Overload * operator to multiply a vector by a scaler
CartVector operator * (CartVector v1, double d)
{
	return CartVector(v1.x * d, v1.y * d);
}

//Overload / operator to divide a vector by a scaler
CartVector operator / (CartVector v1, double d)
{
	return CartVector(v1.x / d, v1.y / d);
}

//Overload << operator to print a vector
std::ostream& operator << (std::ostream &out, CartVector v1)
{
	out << v1.x << ", " << v1.y;
	return out;
}

//Writes a cartvector to a file
void CartVector::save(std::ofstream& file)
{
	file << x << " " << y << " ";
}