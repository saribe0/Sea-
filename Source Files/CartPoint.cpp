#include "CartVector.h"
#include "CartPoint.h" 
#include <cmath>

//Default constructor for a CartPoint at (0,0)
CartPoint::CartPoint()
	{
		x = 0;
		y = 0;
	}

//Constructor for a CartPoint with given coordinates
CartPoint::CartPoint(double in_x, double in_y)
	{
		x = in_x;
		y = in_y;
	}

//Takes two CartPoints and returns the distance between the two
double cart_distance(CartPoint p1, CartPoint p2)
	{
		return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
	}

//Overloads + operator to add a CartVector to a CartPoint
CartPoint operator+ (CartPoint p, CartVector v)
{
	return CartPoint(p.x + v.x, p.y + v.y);
}

//Overloads - operator to subtract two CartPoints to get a CartVector 
CartVector operator- (CartPoint p1, CartPoint p2)
{
	return CartVector(p1.x - p2.x, p1.y - p2.y);
}

//Overloads == operator to determine if two CartPoints are the same
bool operator == (CartPoint p1, CartPoint p2)
{
	if (p1.x == p2.x && p1.y == p2.y)
		return true;
	else
		return false;
}

//Overloads << operator to print a CartPoint in form <(x,y)>
std::ostream& operator<< (std::ostream &out, CartPoint p1)
{
	out << "(" << p1.x << ", " << p1.y << ")";
	return out;
}

//Writes a cartpoint to a file
void CartPoint::save(std::ofstream& file)
{
	file << x << " " << y << " ";
}