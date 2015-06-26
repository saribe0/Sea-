/*A class that creates a cave object which inherits GameObject. A cave is a place
	for a fish to hide in and call its home. It can hide a fish and release a hidden
	fish*/

#ifndef Cave_h
#define Cave_h

class Fish;
class Model;

#include "GameObject.h"

class Cave : public GameObject
{
private:
	double space;
	int inhabitants;

public:
	//Default constructor for a cave. Location (0,0)
	Cave();

	//Constructor that only takes an id
	Cave(int id);

	//Constructor for a cave at given location and id
	Cave(int in_id, CartPoint in_loc);

	//Destructor
	~Cave();

	//Returns the space left in the cave
	double get_space();

	//Returns the number of inhabitants in the cave
	int get_inhabitants();

	//Attempts to hide a fish. If there is room, returns true and reduces the 
	//	space in the cave. IF not, returns false.
	bool hide_fish(Fish* fish_to_hide);

	//Attempts to release a fish. If the fish is hidden, increases the size of
	//	the cave and returns true. If not, returns false.
	bool release_fish(Fish* fish_to_release);

	//Updates the state of the cave depending on the space left in the cave
	bool update();

	//Prints the status of the cave including how much space is left in the cave
	void show_status();

	//Writes class specific information to file
	void save(std::ofstream& file);

	//Reads class specific information from file
	void restore(std::ifstream& file, Model& model);
};

#endif