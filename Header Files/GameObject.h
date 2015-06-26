/*This class is the base class for all the objects in the game.
	It provides basic functions to get information about the object
	and a function to plot the object into an array.*/

#include <fstream>
#include "CartPoint.h"

class Model;

#ifndef GameObject_h
#define GameObject_h

class GameObject
{
private:
	int id_num;

protected:
	CartPoint location;
	char display_code;
	char state;

public:
	//Default Constructor
	GameObject() {}

	//GameObject that takes in a code and an id as parameters
	GameObject(char in_code, int in_id);

	//Overloaded GameObject that take in a code, an id, and a location as parameters
	GameObject(char in_code, int in_id, CartPoint in_loc);

	//Destructor
	virtual ~GameObject();

	//Returns the location of the object
	CartPoint get_location();

	//Returns the id of the object
	int get_id();

	//Returns the state of the object
	char get_state();

	//Returns the display code of the object
	char get_type();

	//Returns true
	virtual bool is_alive();

	//Virtual update()
	virtual bool update() = 0;

	//Shows the status of the object
	virtual void show_status();

	//Draws the object into the gameboard
	void drawself(char* grid);

	//Method to save
	virtual void save(std::ofstream& file);

	//Method to restore
	virtual void restore(std::ifstream& file, Model&model);
};
#endif