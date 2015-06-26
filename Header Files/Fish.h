/*A fish is an object derived from GameObject. A fish has a size and energy
	and can swim from one location to another. It can eat at a coral reef and
	gain in size and can hide in a cave and leave a cave. It can also just float.*/

#ifndef Fish_h
#define Fish_h

#include "CoralReef.h"
#include "cmath"
#include "CartPoint.h"
#include "Cave.h"

class Model;

class Fish : public GameObject
{
protected:
	double energy;
	double size;
	double prefeast_size;
	CartPoint destination;
	CartVector delta;
	CoralReef* reef;
	Cave* home;
	Model* world;

	//Updates the location of the fish. Either arrives or keeps swimming
	bool update_loc();

	//Sets the destination of the fish
	void setup_destination(CartPoint dest);

public:

	//Default constructor creates a fish with a certain code and size
	Fish(char display_code, int size, Model* model);

	//Constructor that creates a fish with a display code and id
	Fish(char display_code, int id, int size, Model* model);

	//Constructor that creates a fish that starts in and with a given cave 
	//	as its home, a certain display code, and a size
	Fish(char display_code, int in_id, Cave* home, int size, Model* model);

	//Constructor that creates a fish that starts in a location that is not
	//	a cave, has a certain display code, and a size
	Fish(char display_code, int in_id, CartPoint loc, int size, Model* model);

	//Destructor
	~Fish();

	//Returns false, if the fish is dead, true if alive
	bool is_alive();

	//Takes away from a fishes energy (health). Can kill the fish or just hurt it
	void get_bitten(int attack_strength);

	//Speed of fish
	virtual double get_speed() = 0;

	//Returns the size of the fish
	double get_size();

	//Returns true if the fish is hidden, false if not
	bool is_hidden();

	//Template for attacking
	virtual void start_attack(Fish*attacker);

	//Template for mating
	virtual bool start_mating(Fish*mate);

	//Tells the fish to start swimming to a destination
	void start_swimming(CartPoint dest);

	//Tells the fish to start eating from a given reef
	void start_eating(CoralReef *destReef);

	//Tells the fish to hid in a given cave and starts the process
	void start_hiding(Cave *destCave);

	//Tells the fish to float in place without moving
	void float_in_place();

	//Updates the fish's state
	virtual bool update();

	//Prints the status of the fish
	void show_status();

	//Writes class specific details to file
	virtual void save(std::ofstream& file);

	//Method to restore
	virtual void restore(std::ifstream& file, Model&model);
};

#endif