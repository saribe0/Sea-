/*The Sharknado is a singleton class. There can only be one Sharknado
	and it is persistent between runs of the game (save/restor). The
	Sharknado sweeps away all fish objects dead or alive that are not
	hidden every 15 time ticks. It gives a warning 5 ticks before it 
	comes.*/

#include <iostream>
#include <list>
#include "Fish.h"

class Model;

#ifndef Sharknado_h
#define Sharknado_h

class Sharknado : public GameObject
{
private:
	std::list<Fish*> swept_away;
	std::list<Fish*> swept_away_once;
	Model* world;

	Sharknado(){}
	Sharknado(Sharknado const&);
	void operator = (Sharknado const&);
	Sharknado(Model* model);


public:
	//Constructor
	static Sharknado* getInstance(Model* model);
	
	//Destructor
	~Sharknado();

	//Returns true
	bool is_alive();

	//Deletes all the fish that were swept away by the Sharknado
	void deleteSweptFish();

	//Prints all the fish swept away by the Sharknado
	void print_fish_swept_away();

	//Checks the Sharknado clock and acts accordingly
	bool update();

	//Does nothing
	void show_status() {}

	//Method to save
	void save(std::ofstream& file);

	//Method to restore
	void restore(std::ifstream& file, Model&model);
};

#endif