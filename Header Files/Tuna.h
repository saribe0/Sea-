/*A class that creates a Tuna, an object derived from a Fish. A Tuna
	can do much the same as a normal fish with the addition of being
	able to mate and produce new Tuna objects*/

#ifndef Tuna_h
#define Tuna_h

#include "Fish.h"

class Model;

class Tuna : public Fish
{
private:
	int mate_time;
	Fish* mate;

public:
	//Default constructor
	Tuna(Model* model);

	//Constructor that just takes an ID
	Tuna(int id, Model* model);

	//Overloaded constructor that takes a cave as a home and an id
	Tuna(int id, Cave* home, Model* model);

	//Destructor
	~Tuna();

	//Returns the potential speed of the fish
	double get_speed();

	//Mates the tuna with the passed in tuna
	bool start_mating(Tuna *fish_mate);

	//Updates the Tuna
	bool update();

	//Shows the Tuna's status
	void show_status();

	//Writes class specific information to file
	void save(std::ofstream& file);

	//Reads class specific information from file
	void restore(std::ifstream& file, Model& model);
};
#endif