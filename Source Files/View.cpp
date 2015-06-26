#include "View.h"

//Gets the row and column that the locatoin passed should be plotted in the array
bool View::get_subscripts(int &ix, int &iy, CartPoint location)
{
	CartVector xy = (location - origin) / scale;
	ix = (int)xy.x;
	iy = (int)xy.y;
	if (ix > view_maxsize / scale || iy > view_maxsize / scale || ix < 0 || iy < 0)
	{
		std::cout << "An object is outside the display" << std::endl;
		return false;
	}
	else
		return true;
}

//Constructor sets the size, scale and origin of the view.
View::View()
{
	size = 11;
	scale = 2;
	origin = CartPoint();
}

//Sets all value of the view array to either '.' or ' ' depending on the location
void View::clear()
{
	for (int i = 0; i < view_maxsize+2; i += (int)scale)
		for (int j = 0; j < view_maxsize+2; j += (int)scale)
		{
			grid[i][j][0] = '.';
			grid[i + 1][j][0] = ' ';
			grid[i][j][1] = ' ';
			grid[i + 1][j][1] = ' ';
		}
}

//Gets objects to draw themselves into the spot in the array
void View::plot(GameObject* ptr)
{
	int x;
	int y;
	if (get_subscripts(x, y, ptr->get_location()))
		ptr->drawself(grid[x * (int)scale][(int)scale*y]);
}

//Prints the view to the console
void View::draw()
{
	for (int j = view_maxsize; j >= 0; j -= (int)scale*2)
	{
		//Prints lines starting with a y-value
		std::cout << j;
		if (j < 10)
			std::cout << " "; //prints a space after y-values less than 10 to make them even
		for (int i = 0; i <= view_maxsize; i += (int)scale)
		{
			std::cout << grid[i][j][0];
			if (i != view_maxsize || grid[i][j][1] != ' ') //don't print a trailing space
				std::cout << grid[i][j][1];
		}
		if (j != 0)
		{
			std::cout << std::endl << "  "; //spaces to make up for not haveing y-values
			for (int i = 0; i <= view_maxsize; i += (int)scale)
			{
				std::cout << grid[i][j - (int)scale][0];
				if (i != view_maxsize || grid[i][j-(int)scale][1] != ' ') //don't print a trailing space
					std::cout << grid[i][j - (int)scale][1];
			}
		}
		std::cout << std::endl;
	}
	std::cout << "  0   4   8   12  16  20" << std::endl; //x-axis
}