/*This class is derived from GameObject. It creates a "Coral Reef"
	where fish can eat and gain in size. There is a limited amount of food*/

#ifndef CoralReef_h
#define CoralReef_h

#include "GameObject.h"

class Model;

class CoralReef: public GameObject
{
private:
	double amount;

public:

	//Default constructor. Creates a reef at (0,0)
	CoralReef();

	//Constructor that only takes an id
	CoralReef(int id);

	//Overloaded constructor which gives the reef the inputed id and location
	CoralReef(int in_id, CartPoint in_loc);

	//Destructor
	~CoralReef();

	//Returns true if the reef is out of food
	bool is_empty();
	
	//Provides food. Returns the amount provided and subtracts it from the reef's amount
	double provide_food(double amount_to_provide = 20.0);
	
	//Updates the state of the reef. State depends on whether the reef has food left
	bool update();
	
	//Prints the status of the reef
	void show_status();
	
	//Writes class specific information to file
	void save(std::ofstream& file);

	//Reads class specific information from file
	void restore(std::ifstream& file, Model& model);
};

#endif