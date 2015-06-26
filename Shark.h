/*A class that creates a Shark object, derived from a Fish. Sharks 
	can not move and are spawned randomely using the game's time as 
	a seed. If another fish gets close enough, a shark can attack it.*/

#ifndef Shark_h
#define Shark_h

#include "Fish.h"

class Model;

class Shark : public Fish
{
private:
	int attack_strength;
	double range;
	Fish *target;

	//Makes a random point to assign the sharks location to
	CartPoint rand_cartpoint(Model* model);

public:
	//Default constructor
	Shark(Model* model);

	//Overloaded constructor that takes a cave as a home and an id
	Shark(int id, Model* model);

	//Overloaded constructor which takes an id and the initial position of the Shark
	Shark(int id, CartPoint loc, Model* model);

	//Destructor
	~Shark();

	//Returns the potential speed of the fish
	double get_speed();

	//Starts attacking another fish
	void start_attack(Fish *target);

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