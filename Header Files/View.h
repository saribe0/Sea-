/*This class creates a gameboard/grid that allows objects to plot themselves
	and allows it to be printed to the console*/

#include "GameObject.h"

#ifndef View_h
#define View_h

const int view_maxsize = 20;

class View
{
private:
	int size;
	double scale;
	CartPoint origin;
	char grid[view_maxsize + 2][view_maxsize + 2][2];

	//Gets the row and column that the locatoin passed should be plotted in the array
	bool get_subscripts(int &ix, int &iy, CartPoint location);

public:
	//Constructor sets the size, scale and origin of the view.
	View(); 

	//Sets all value of the view array to either '.' or ' ' depending on the location
	void clear();

	//Gets objects to draw themselves into the spot in the array
	void plot(GameObject* ptr);

	//Prints the view to the console
	void draw();
};
#endif