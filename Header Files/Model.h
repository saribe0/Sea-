/*This class creates a series of tuna, sharks, caves, coral reefs, and 
	one sharknado and saves pointers to them in lists. It provides functions 
	to get pointers to objects specified by their ID, to update each object,
	and to show the status of each function. It also executes the code 
	to print the view. Each model is essentially one instantiation
	of a sea.*/

#include "Fish.h"
#include "View.h"
#include "Tuna.h"
#include "Shark.h"
#include "Cave.h"
#include "Sharknado.h"
#include <list>

#ifndef Model_h
#define Model_h

class Model
{
public:
	int time;
	std::list<GameObject*> object_ptrs;
	std::list<GameObject*> active_ptrs;
	std::list<Fish*> fish_ptrs;
	std::list<Cave*> cave_ptrs;
	std::list<CoralReef*> reef_ptrs;
	
	//Constructor creates 2 caves, 3 coral reefs and 2 fish
	//Also creates 5 lists to hold pointers to all these objects
	Model();
	
	//Destructor deletes all objects in the game
	~Model();
	
	//Returns the pointer to the fish with the passed in ID
	Fish* get_Fish_ptr(int id_num);
	
	//Returns the pointer to the Coral Reef with the passed in ID
	CoralReef* get_CoralReef_ptr(int id_num);
	
	//Returns the pointer to the Cave with the passed in ID
	Cave* get_Cave_ptr(int id_num);

	//Adds the object at the end of the proper list
	void add_new_object(GameObject* object);
	
	//Returns next available fish ID
	int get_next_Fish_id();

	//Updates all the objects by calling each of their update functions
	bool update();
	
	//Shows the status of every object on the gameboard
	void show_status();

	//Prints the time and calls the plot and draw function of the view class to print the gameboard
	void display(View& view);

	//Writes model information to file
	void save(std::ofstream& file);

	//Reads a model from file
	void restore(std::ifstream& file);

};

#endif